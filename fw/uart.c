#include "uart.h"
#include "LPC8xx.h"

void uart_initialize(void)
{
    /* enable clock */
    LPC_SYSCON->SYSAHBCLKCTRL |= (1 << UART_CLK_EN);
    
    /* clear resets */
    /* todo */

    /* switch matrix */
    LPC_SWM->PINASSIGN0 |= (TX_PIN << TX_EN_POS);
    LPC_SWM->PINASSIGN0 |= (RX_PIN << RX_EN_POS);

    /* configure baud for 9600 */
    /* U_PCLK = UARTCLKDIV/(1 + MULT/DIV) */

    /* main uart peripheral clock */
    LPC_SYSCON->UARTCLKDIV = 200;

    /* fractional generator */
    LPC_SYSCON->UARTFRGDIV = 0xFF; /* 0xFF + 0x01 = 256 */
    LPC_SYSCON->UARTFRGMULT = 44;

    /* baud rate = U_PCLK/16 x BRGVAL */
    LPC_USART0->BRG = 3;

    /* configure for 8 bits, no parity, 1 stop bit */
    LPC_USART0->CFG = (1 << UART_EN_POS) || (1 << UART_LEN_POS);
}


void uart_print_char(char c)
{
    /* wait until tx ready */
    while (!(LPC_USART0->STAT & (1 << UART_TXRDY)));
    LPC_USART0->TXDATA = c;
}


void uart_print(char *str)
{
    char *c = str;
    while (*c != '\0')
    {
        uart_print_char(*c);
        c++;
    }
}


void uart_irq(void)
{
}

