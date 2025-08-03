#include "LPC8xx.h"
#include "display.h"

/* Delay for some time. */
static void display_delay(int counts)
{
    for (int i = 0; i < counts; i++);
}


/* Pulse SRCLK and RCLK to latch serial values. */
static void display_pulse_clk(void)
{
    LPC_GPIO_PORT->SET0 |= (1 << SRCLK_PIN);
    LPC_GPIO_PORT->CLR0 |= (1 << RCLK_PIN);
    display_delay(DELAY_CNTS);
    LPC_GPIO_PORT->CLR0 |= (1 << SRCLK_PIN);
    LPC_GPIO_PORT->SET0 |= (1 << RCLK_PIN);
    display_delay(DELAY_CNTS);
}


/* Clock value into shift register. */
static void display_set_shift(uint8_t *values)
{
    int shift_cnt = 8;
    for (int i = 0; i < shift_cnt; i++)
    {
        /* set data */
        LPC_GPIO_PORT->B0[SER1_PIN] = (display_table[values[0]] >> i) & LSB_MASK;
        LPC_GPIO_PORT->B0[SER2_PIN] = (display_table[values[1]] >> i) & LSB_MASK;
        LPC_GPIO_PORT->B0[SER3_PIN] = (display_table[values[2]] >> i) & LSB_MASK;
        LPC_GPIO_PORT->B0[SER4_PIN] = (display_table[values[3]] >> i) & LSB_MASK;
        LPC_GPIO_PORT->B0[SER5_PIN] = (display_table[values[4]] >> i) & LSB_MASK;
        LPC_GPIO_PORT->B0[SER6_PIN] = (display_table[values[5]] >> i) & LSB_MASK;

        display_pulse_clk();
    }

    /* reset pins */
    LPC_GPIO_PORT->CLR0 |= (1 << SRCLK_PIN);
    LPC_GPIO_PORT->SET0 |= (1 << RCLK_PIN);
}


/* Initialize pins and shift registers to zero. */
void display_initialize(void)
{   
    /* disable SWCLK function (bit 2) so PIO0_3 can be used as GPIO */
    LPC_SWM->PINENABLE0 |= (1 << 2);

    /* set pins as outputs */
    LPC_GPIO_PORT->DIR0 |= (1 << SRCLR_PIN) | (1 << RCLK_PIN) | (1 << SRCLK_PIN) |
                           (1 << SER1_PIN)  | (1 << SER2_PIN) | (1 << SER3_PIN)  |
                           (1 << SER4_PIN)  | (1 << SER5_PIN) | (1 << SER6_PIN);

    LPC_GPIO_PORT->CLR0 |= (1 << SRCLR_PIN) | (1 << RCLK_PIN) | (1 << SRCLK_PIN) |
                           (1 << SER1_PIN)  | (1 << SER2_PIN) | (1 << SER3_PIN)  |
                           (1 << SER4_PIN)  | (1 << SER5_PIN) | (1 << SER6_PIN);

    /* reset registers */
    display_delay(DELAY_CNTS);
    LPC_GPIO_PORT->SET0 |= (1 << SRCLR_PIN);
    display_delay(DELAY_CNTS);

    uint8_t values[6] = {0, 0, 0, 0, 0, 0};
    display_set_shift(values);
}

