#include "LPC8xx.h"
#include "display.h"
#include "i2c.h"
#include "uart.h"

int main(void)
{
    display_initialize();
    uart_initialize();
    i2c_initialize();

    while (1)
    {
        uart_print_char('a');
        for (int i = 0; i < 100000; i++);
    }

    return 1;
}

