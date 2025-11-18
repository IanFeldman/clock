#include "LPC8xx.h"
#include "display.h"
#include "i2c.h"
#include "uart.h"
#include "main.h"

volatile uint8_t pps_flag = 0;

static void increment_time(rtc_time_t *time);

int main(void)
{
    display_initialize();
    uart_initialize();
    i2c_initialize();

    /* reset terminal */
    uart_print_esc(CLEAR_SCREEN);
    uart_print_esc(HOME_CURSOR);

    /* initialize pps pin */
    pps_initialize();

    /* initalize time */
    i2c_rtc_output_config();
    rtc_time_t time = { 0, 0, 0, 0, 0 };
    i2c_rtc_set_time(time);

    while (1)
    {
        /* 1Hz */
        if (pps_flag)
        {
            /* update display with updated time */
            increment_time(&time);
            display_set_shift((uint8_t *)&time);
            pps_flag = 0;
        }
    }

    return 1;
}


/* Enable external rising edge interrupt for PPS pin on PININT0 */
void pps_initialize(void)
{
    /* disable SWDIO function (bit 3) so PIO0_2 can be used as GPIO */
    LPC_SWM->PINENABLE0 |= (1 << 3);
    /* set input */
    LPC_GPIO_PORT->DIR0 &= ~(1 << PPS_PIN);
    /* set external interrupt */
    LPC_SYSCON->PINTSEL[PPS_IRQ] = PPS_PIN;
    /* enable edge sensitive */
    LPC_PIN_INT->ISEL &= ~(1 << PPS_IRQ);
    /* enable rising edge detect */
    LPC_PIN_INT->IENR |= (1 << PPS_IRQ);
    /* clear nay pending/leftover flags */
    LPC_PIN_INT->IST = 0xFF;
    /* enable interrupt */
    NVIC_EnableIRQ(PININT0_IRQn);
}


static void increment_time(rtc_time_t *time)
{
    time->seconds_ones++;
    /* check seconds */
    if (time->seconds_ones > 9)
    {
        time->seconds_ones = 0;
        time->seconds_tens++;
    }
    if (time->seconds_tens > 5)
    {
        time->seconds_tens = 0;
        time->minutes_ones++;
    }

    /* check minutes */
    if (time->minutes_ones > 9)
    {
        time->minutes_ones = 0;
        time->minutes_tens++;
    }
    if (time->minutes_tens > 5)
    {
        time->minutes_tens = 0;
        time->hours_ones++;
    }

    /* check hours */
    if (time->hours_ones > 9)
    {
        time->hours_ones = 0;
        time->hours_tens++;
    }
    if ((time->hours_tens == 2) && (time->hours_ones > 3))
    {
        time->hours_tens = 0;
        time->hours_ones = 0;
    }
}


/* RTC PPS external interrrupt */
void PININT0_IRQHandler(void) {
    /* check interrupt flag */
    if (LPC_PIN_INT->IST & (1 << PPS_IRQ))
    {
        pps_flag = 1;
        LPC_PIN_INT->IST = (1 << PPS_IRQ);
    }
}

