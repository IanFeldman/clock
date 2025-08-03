#ifndef DISPLAY_H
#define DISPLAY_H

#define DELAY_CNTS 100

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

static const uint8_t display_table[10] =
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
};

void display_initialize(void);

#endif /* DISPLAY_H */

