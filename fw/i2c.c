#include "i2c.h"
#include "LPC8xx.h"

void i2c_initialize(void)
{
    /* enable clock */
    LPC_SYSCON->SYSAHBCLKCTRL |= (1 << I2C_CLK_EN);

    /* assert i2c reset */
    LPC_SYSCON->PRESETCTRL &= ~I2C_RST_N;

    /* switch matrix */
    LPC_SWM->PINASSIGN7 |= (SDA_PIN << SDA_EN_POS);
    LPC_SWM->PINASSIGN8 |= (SCL_PIN << SCL_EN_POS);

    /* clock speed */
    /* todo */

    /* set as master */
    LPC_I2C->CFG = (1 << 0);
}

