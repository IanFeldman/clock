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

    uint8_t i = 0;
    while (1)
    {
        uart_print_ln("Hello, world");
        uint8_t values[6] = { i, i, i, i, i, i };
        display_set_shift(values);
        i++;
        if (i > 9) {i = 0;}
        for (int i = 0; i < 1000000; i++);
    }

    return 1;
}

