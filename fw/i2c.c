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
    LPC_I2C->CFG = (1 << I2C_MSTEN);
}

void i2c_tx(uint8_t addr, uint8_t *data, int size)
{
    /* write address */
    LPC_I2C->MSTDAT = addr;
    /* start transaction */
    LPC_I2C->MSTCTL = (1 << I2C_MSTSTART);
    /* wait for send to complete */
    while (!(LPC_I2C->STAT & (1 << I2C_MSTPENDING)));

    /* perform data transaction */
    for (int i = 0; i < size; i++)
    {
        LPC_I2C->MSTDAT = data[i];
        /* indicate to continue */
        LPC_I2C->MSTCTL = (1 << I2C_MSTCONT);
        /* wait for send to complete */
        while (!(LPC_I2C->STAT & (1 << I2C_MSTPENDING)));
    }

    /* stop transaction */
    LPC_I2C->MSTCTL = (1 << I2C_MSTSTOP);
}

void i2c_irq(void) {
    return;
}

