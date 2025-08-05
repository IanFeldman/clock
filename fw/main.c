#include "LPC8xx.h"
#include "display.h"
#include "i2c.h"

int main(void)
{
    display_initialize();
    i2c_initialize();

    while (1)
    {
        for (volatile int i = 0; i < 500000; i++); // Delay
    }

    return 1;
}

