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

#define UARTFRG_RST_N   2
#define UART0_RST_N     3

#define ESC_CHAR 0x1b
#define NEW_LINE "[1E"
#define HOME_CURSOR "[H"
#define CLEAR_SCREEN "[2J"

void uart_initialize(void);
void uart_print(char *str);
void uart_print_ln(char *str);
void uart_print_esc(char *code);
void uart_print_char(char c);
void uart_print_hex(char val);
void uart_irq(void);

#endif /* UART_H */

