#ifndef DISPLAY_H
#define DISPLAY_H

#define GPIO_CLK_EN 6
#define DELAY_CNTS 1

#define SRCLR_PIN 12  /* active low clear */
#define RCLK_PIN   3  /* shift clock */
#define SRCLK_PIN  6  /* overall clock */

#define SER1_PIN 13
#define SER2_PIN 14
#define SER3_PIN 15
#define SER4_PIN 16
#define SER5_PIN 17
#define SER6_PIN  7

#define LSB_MASK 0x01

/* indices of non-numerical display symbols */
#define DSP_CLR 10
#define DSP_DEG 11
#define DSP_F   12
#define DSP_C   13

static const uint8_t display_table[14] =
{
    0x03, /* 0 */
    0x9F, /* 1 */
    0x25, /* 2 */
    0x0D, /* 3 */
    0x99, /* 4 */
    0x49, /* 5 */
    0x41, /* 6 */
    0x1F, /* 7 */
    0x01, /* 8 */
    0x19, /* 9 */
    0xFF, /* clear   (10) */
    0x39, /* degrees (11) */
    0x71, /* f       (12) */
    0x63, /* c       (13) */
};

void display_initialize(void);
void display_set(uint8_t *values);
void display_clear(void);

#endif /* DISPLAY_H */

