#ifndef UART_H
#define UART_H

/* uart0 */
#define UART_CLK_EN 14
#define TX_PIN (uint8_t)4
#define RX_PIN (uint8_t)0
#define TX_EN_POS       0
#define RX_EN_POS       8

#define UART_EN_POS     0
#define UART_LEN_POS    2      
#define UART_TXRDY      2

void uart_initialize(void);
void uart_print_char(char c);
void uart_print(char *str);
void uart_irq(void);

#endif /* UART_H */

