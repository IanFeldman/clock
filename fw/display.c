#include "LPC8xx.h"
#include "display.h"

/* Delay for some time */
static void display_delay(void)
{
    for (int i = 0; i < DELAY_CNTS; i++);
}


/* Set the value of a single shift register */
static void display_set_shift(uint16_t shift_register, uint8_t value)
{
    int shift_cnt = 8;
    for (int i = 0; i < shift_cnt; i++)
    {
        /* clock goes low */
        LPC_GPIO_PORT->CLR0 |= SR_CLOCK_PIN;
        /* shift goes high (after first time) */
        if (i > 0) LPC_GPIO_PORT->SET0 |= SR_SHIFT_PIN;
        /* set data */
        LPC_GPIO_PORT->B0[shift_register] = (value >> i) & 0x01;
        /* hold */
        display_delay();
        /* clock goes high */
        LPC_GPIO_PORT->SET0 |= SR_CLOCK_PIN;
        /* shift goes low (after first time) */
        if (i > 0) LPC_GPIO_PORT->CLR0 |= SR_SHIFT_PIN;
        /* hold */
        display_delay();
    }
}


/* Initialize pins and shift registers to zero */
void display_initialize(void)
{
    /* set pins as outputs */
    LPC_GPIO_PORT->DIR0 |= SR_CLEAR_PIN | SR_CLOCK_PIN | SR_SHIFT_PIN |
                           SR_DATA1_PIN | SR_DATA2_PIN | SR_DATA3_PIN |
                           SR_DATA4_PIN | SR_DATA5_PIN | SR_DATA6_PIN;

    /* set pins to defaults */
    LPC_GPIO_PORT->SET0 |= SR_CLEAR_PIN;
    LPC_GPIO_PORT->CLR0 |= SR_CLOCK_PIN | SR_SHIFT_PIN | SR_DATA1_PIN |
                           SR_DATA2_PIN | SR_DATA3_PIN | SR_DATA4_PIN |
                           SR_DATA5_PIN | SR_DATA6_PIN;

    display_set_shift(SR_DATA1, 0xFF);
}

