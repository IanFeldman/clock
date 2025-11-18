#ifndef MAIN_H
#define MAIN_H

#define PPS_PIN 2
#define PPS_IRQ 0 /* PININT0_IRQ */
#define PPS_NVIC_NUM 24 /* interrupt 24 in NVIC */

void PININT0_IRQHandler(void);

#endif /* MAIN_H */

