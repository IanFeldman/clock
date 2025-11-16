#include "LPC8xx.h"
#include "display.h"
#include "i2c.h"
#include "uart.h"

int main(void)
{
    display_initialize();
    uart_initialize();
    i2c_initialize();

    /* reset terminal */
    uart_print_esc(CLEAR_SCREEN);
    uart_print_esc(HOME_CURSOR);
    uart_print_ln("Clock initialized");

    /* initalize time */
    rtc_time_t time = { 0, 0, 0, 0, 0 };
    i2c_rtc_set_time(time);

    while (1)
    {
        /* get time */
        rtc_time_t time = i2c_rtc_get_time();
        display_set_shift((uint8_t *)&time);
        uart_print_ln("Display updated");
        for (int i = 0; i < 1000000; i++);
    }

    return 1;
}

