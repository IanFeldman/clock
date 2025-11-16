#ifndef I2C_H
#define I2C_H

#include <stdint.h>

#define SDA_PIN (uint8_t)11
#define SCL_PIN (uint8_t)10
#define SDA_EN_POS       24
#define SCL_EN_POS        0
#define I2C_CLK_EN        5
#define I2C_RST_N         6
#define I2C_MSTEN         0
#define I2C_MSTCONT       0
#define I2C_MSTSTART      1
#define I2C_MSTSTOP       2
#define I2C_MSTPENDING    0
#define I2C_READWRITE     0

#define RTC_CHIP_ADDR 0xDE
#define RTC_SEC_ADDR 0x00
#define RTC_MIN_ADDR 0x01
#define RTC_HRS_ADDR 0x02

typedef struct {
    uint8_t seconds;
    uint8_t minutes;
    uint8_t hours;
} rtc_time_t;

void i2c_initialize(void);
void i2c_tx(uint8_t chip_addr, uint8_t addr, uint8_t *data, int size);
void i2c_rx(uint8_t chip_addr, uint8_t addr, uint8_t *data, int size);

/* rtc functions */
rtc_time_t i2c_rtc_get_time(void);
void i2c_rtc_set_time(rtc_time_t time);

#endif /* I2C_H */

