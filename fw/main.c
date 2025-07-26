#include "LPC8xx.h"
#include "display.h"

int main(void)
{
    display_initialize();

    while (1)
    {
        for (volatile int i = 0; i < 500000; i++); // Delay
    }

    return 1;
}

