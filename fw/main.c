#include "LPC8xx.h"
#include "display.h"

int main(void)
{
    LPC_GPIO_PORT->DIR0 = (1 << 17);
    while (1)
    {
        LPC_GPIO_PORT->NOT0 = (1 << 17);  // Toggle P0_17
        for (volatile int i = 0; i < 500000; i++); // Delay
    }

    return 1;
}

