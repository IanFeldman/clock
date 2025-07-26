#ifndef DISPLAY_H
#define DISPLAY_H

#define DELAY_CNTS 100

#define SR_CLEAR_PIN (1 << 12)  /* clear display - active low */
#define SR_CLOCK_PIN (1 <<  3)  /* overall clock */
#define SR_SHIFT_PIN (1 << 11)  /* shift data */

#define SR_DATA1 13
#define SR_DATA2 14
#define SR_DATA3 15
#define SR_DATA4 16
#define SR_DATA5 17
#define SR_DATA6  7
#define SR_DATA1_PIN (1 << SR_DATA1)
#define SR_DATA2_PIN (1 << SR_DATA2)
#define SR_DATA3_PIN (1 << SR_DATA3)
#define SR_DATA4_PIN (1 << SR_DATA4)
#define SR_DATA5_PIN (1 << SR_DATA5)
#define SR_DATA6_PIN (1 << SR_DATA6)

void display_initialize(void);


#endif /* DISPLAY_H */
