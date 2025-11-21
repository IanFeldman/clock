#ifndef MAIN_H
#define MAIN_H

#define PPS_PIN 2
#define PPS_IRQ 0 /* PININT0_IRQ */

#define MODE_PIN 1
#define MODE_IRQ 1 /* PININT1_IRQ */

void PININT0_IRQHandler(void);
void PININT1_IRQHandler(void);
void UART0_IRQHandler(void);

#endif /* MAIN_H */

