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

void i2c_initialize(void);
void i2c_irq(void);
void i2c_tx(uint8_t addr, uint8_t *data, int size);

#endif /* I2C_H */

