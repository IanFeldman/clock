#include "i2c.h"
#include "LPC8xx.h"

/* Initialize I2C peripheral as master at 100kHz */
void i2c_initialize(void)
{
    /* enable clock */
    LPC_SYSCON->SYSAHBCLKCTRL |= (1 << I2C_CLK_EN);

    /* assert i2c reset */
    LPC_SYSCON->PRESETCTRL |= (1 << I2C_RST_N);

    /* switch matrix */
    LPC_SWM->PINASSIGN7 |= (SDA_PIN << SDA_EN_POS);
    LPC_SWM->PINASSIGN8 |= (SCL_PIN << SCL_EN_POS);

    /* clock speed */
    /* 48 MHz / 480 = 100kHz (standard mode) */
    LPC_I2C->DIV = 480;

    /* set as master */
    LPC_I2C->CFG = (1 << I2C_MSTEN);
}


/* Perform I2C write to address */
void i2c_tx(uint8_t chip_addr, uint8_t data_addr, uint8_t *data, int size)
{
    /* write slave address with read/~write bit set to 0 */
    chip_addr &= ~(1 << I2C_READWRITE);
    /* start the transmission */
    LPC_I2C->MSTCTL = (1 << I2C_MSTSTART);
    /* wait for pending status to be set */
    while (!(LPC_I2C->STAT & (1 << I2C_MSTPENDING)));
    /* write 8 bits of data address */
    LPC_I2C->MSTDAT = data_addr;
    /* indicate to continue */
    LPC_I2C->MSTCTL = (1 << I2C_MSTCONT);
    /* wait for pending status to be set */
    while (!(LPC_I2C->STAT & (1 << I2C_MSTPENDING)));

    /* write remaining data */
    for (int i = 0; i < size; i++)
    {
        /* write 8 bits of data */
        LPC_I2C->MSTDAT = data[i];
        /* indicate to continue */
        LPC_I2C->MSTCTL = (1 << I2C_MSTCONT);
        /* wait for pending status to be set */
        while (!(LPC_I2C->STAT & (1 << I2C_MSTPENDING)));
    }

    /* stop transaction */
    LPC_I2C->MSTCTL = (1 << I2C_MSTSTOP);
}


/* Perform I2C read from address */
void i2c_rx(uint8_t chip_addr, uint8_t data_addr, uint8_t *data, int size)
{
    /* ===== write ===== */

    /* write slave address with read/~write bit set to 0 */
    chip_addr &= ~(1 << I2C_READWRITE);
    /* start the transmission */
    LPC_I2C->MSTCTL = (1 << I2C_MSTSTART);
    /* wait for pending status to be set */
    while (!(LPC_I2C->STAT & (1 << I2C_MSTPENDING)));
    /* write 8 bits of data address */
    LPC_I2C->MSTDAT = chip_addr;
    /* indicate to continue */
    LPC_I2C->MSTCTL = (1 << I2C_MSTCONT);
    /* wait for pending status to be set */
    while (!(LPC_I2C->STAT & (1 << I2C_MSTPENDING)));

    /* ===== read ===== */
    /* write slave address with read/~write bit set to 1 */
    chip_addr |= (1 << I2C_READWRITE);
    /* restart the transmission */
    LPC_I2C->MSTCTL = (1 << I2C_MSTSTART);

    /* read data */
    for (int i = 0; i < size; i++)
    {
        /* wait for pending status to be set */
        while (!(LPC_I2C->STAT & (1 << I2C_MSTPENDING)));
        /* read byte of data */
        data[i] = LPC_I2C->MSTDAT;
        while (!(LPC_I2C->STAT & (1 << I2C_MSTPENDING)));

        /* continue (not on last byte) */
        if (i < size - 1)
        {
            LPC_I2C->MSTCTL = (1 << I2C_MSTCONT);
        }
    }

    /* stop transaction */
    LPC_I2C->MSTCTL = (1 << I2C_MSTSTOP);
}


/* Get current seconds, minutes, hours from RTC */
void i2c_rtc_set_time(rtc_time_t time)
{
    i2c_tx(RTC_CHIP_ADDR, RTC_HRS_ADDR, &time.hours,   sizeof(time.hours));
    i2c_tx(RTC_CHIP_ADDR, RTC_MIN_ADDR, &time.minutes, sizeof(time.minutes));
    /* enable oscillator  */
    time.seconds |= (1 << 7);
    i2c_tx(RTC_CHIP_ADDR, RTC_SEC_ADDR, &time.seconds, sizeof(time.seconds));
}


/* Get current seconds, minutes, hours from RTC */
rtc_time_t i2c_rtc_get_time(void)
{
    /* get seconds */
    uint8_t seconds_data;
    i2c_rx(RTC_CHIP_ADDR, RTC_SEC_ADDR, &seconds_data, sizeof(seconds_data));
    uint8_t seconds_ones = seconds_data & 0x0F;
    uint8_t seconds_tens = (seconds_data & 0x70) >> 4;

    rtc_time_t time;
    time.seconds = (seconds_tens * 10) + seconds_ones;
    time.minutes = 0;
    time.hours = 0;

    return time;
}

