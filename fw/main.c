#include "LPC8xx.h"
#include "display.h"
#include "i2c.h"
#include "uart.h"
#include "main.h"

void PININT0_IRQHandler(void) {
    /* check interrupt flag */
    if (LPC_PIN_INT->IST & (1 << PPS_IRQ))
    {
        uart_print_ln("Interrupt detected");
        LPC_PIN_INT->IST = (1 << PPS_IRQ);
    }
}


int main(void)
{
    display_initialize();
    uart_initialize();
    i2c_initialize();

    /* reset terminal */
    uart_print_esc(CLEAR_SCREEN);
    uart_print_esc(HOME_CURSOR);
    uart_print_ln("Clock initialized");

    /* initialize pps pin */
    /* disable SWDIO function (bit 3) so PIO0_2 can be used as GPIO */
    LPC_SWM->PINENABLE0 |= (1 << 3);
    LPC_GPIO_PORT->DIR0 &= ~(1 << PPS_PIN); /* as input */
    LPC_SYSCON->PINTSEL[PPS_IRQ] = PPS_PIN; /* set external interrupt */
    // LPC_PIN_INT->ISEL &= ~(1 << PPS_IRQ); /* enable edge sensitive */
    LPC_PIN_INT->ISEL = 0; /* enable edge sensitive */
    // LPC_PIN_INT->IENR |= (1 << PPS_IRQ); /* enable rising edge detect */
    LPC_PIN_INT->IENR = (1 << PPS_IRQ); /* enable rising edge detect */
    LPC_PIN_INT->IST = 0xFF; /* clear any pending or leftover flags */
    NVIC_EnableIRQ(PININT0_IRQn);

    /* initalize time */
    i2c_rtc_output_config();
    rtc_time_t time = { 0, 0, 0, 0, 0 };
    i2c_rtc_set_time(time);

    while (1)
    {
        /* get time */
        rtc_time_t time = i2c_rtc_get_time();
        display_set_shift((uint8_t *)&time);
        uart_print_ln("Display updated");
        for (int i = 0; i < 1000000; i++);
    }

    return 1;
}

