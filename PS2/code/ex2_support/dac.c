#include <stdint.h>
#include <stdbool.h>

#include "efm32gg.h"


/*
 *Setup the DAC
 *
 * */

void setupDAC()
{
  	*CMU_HFPERCLKEN0 |= (1 << 17); /*Enable DAC clock */
	*DAC0_CTRL = 0x50014; /*Prescale clock to yield 437.5 KHz */
	*DAC0_CH0CTRL = 1; /*Enable left channel */
	*DAC0_CH1CTRL = 1; /*Enable right channel */
}

/* 
 * Disable the DAC
 *
 * */

void disableDAC()
{
	*DAC0_CTRL = 0;
	*DAC0_CH0CTRL = 0;
	*DAC0_CH1CTRL = 0;
    *CMU_HFPERCLKEN0 &= ~(1 << 17);

}
