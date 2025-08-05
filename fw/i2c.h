#ifndef I2C_H
#define I2C_H

#define SDA_PIN (uint8_t)11
#define SCL_PIN (uint8_t)10
#define SDA_EN_POS 24
#define SCL_EN_POS 0
#define I2C_CLK_EN 5
#define I2C_RST_N  6

void i2c_initialize(void);

#endif /* I2C_H */

