#include <stdint.h>
#include <stdbool.h>

#include "efm32gg.h"

#define CLOCK_FREQUENCY 14000000

/* function to setup the timer */
void setupTimer(uint16_t period)
{
  /*
    TODO enable and set up the timer
    
    1. Enable clock to timer by setting bit 6 in CMU_HFPERCLKEN0
    2. Write the period to register TIMER1_TOP
    3. Enable timer interrupt generation by writing 1 to TIMER1_IEN
    4. Start the timer by writing 1 to TIMER1_CMD
    
    This will cause a timer interrupt to be generated every (period) cycles. Remember to configure the NVIC as well, otherwise the interrupt handler will not be invoked.
  */  

	*CMU_HFPERCLKEN0 |= (1 << 6);
	*TIMER1_TOP = CLOCK_FREQUENCY/period;
	*TIMER1_IEN = 1;
	*TIMER1_CMD = 1;


 
}


void disableTimer(){
	*CMU_HFPERCLKEN0 &= ~(1 << 6);
	*TIMER1_TOP = 0;
	*TIMER1_IEN = 0;
	*TIMER1_CMD = 0;
}

void setupLowEnergyTimer(){
	
	*CMU_OSCENCMD = (1 << 6);
	*CMU_HFCORECLKEN0 |= (1 << 4); 					/* Enable LE clock */
	*LETIMER0_CTRL |= (1 << 9); 					/* Set COMP0 as TOP register*/
	*CMU_LFACLKEN0 |= (1 << 2);		                /* Enable LOW energy timer 0 */
	*LETIMER0_TOP = 1;								/* Set TOP to 1 */
	*LETIMER0_IEN = 1;							    /* Enable interrupts */
	*LETIMER0_CMD = 1;							    /* Start timer  Start timer */ 

}


