#include <stdint.h>
#include <stdbool.h>

#include "efm32gg.h"

#define CLOCK_FREQUENCY 14000000

/* function to setup the timer.
 * This function is obselete. 
 * Not used in the energy
 * optimized version. 
 */

void setupTimer(uint16_t period)
{

	*CMU_HFPERCLKEN0 |= (1 << 6);
	*TIMER1_TOP = CLOCK_FREQUENCY/period;
	*TIMER1_IEN = 1;
	*TIMER1_CMD = 1; 
}

/*Function to disable the timer.
 * This function is obselete.
 * Not used in the energy
 * optimized version
 * */

void disableTimer()
{
	*CMU_HFPERCLKEN0 &= ~(1 << 6);
	*TIMER1_TOP = 0;
	*TIMER1_IEN = 0;
	*TIMER1_CMD = 0;
}

/* Function to setup the low energy timer.
 * This function configures the timer 
 * with a sample rate of 32768
 */

void setupLowEnergyTimer(){	
	*CMU_OSCENCMD = (1 << 6);						/* Enable the low frequency ocelator */
	*CMU_HFCORECLKEN0 |= (1 << 4); 					/* Enable LE clock */
	*LETIMER0_CTRL |= (1 << 9); 					/* Set COMP0 as TOP register*/
	*CMU_LFACLKEN0 |= (1 << 2);		                /* Enable LOW energy timer 0 */
	*LETIMER0_TOP = 1;								/* Set TOP to 1 */
	*LETIMER0_IEN = 1;							    /* Enable interrupts */
	*LETIMER0_CMD = 1;								/* Start timer  Start timer */ 

}

/* Function to change the sample rate.
 * Used to tune the sample rate
 * to be able to play 8000Hz
 * samples. 
 */

void changeTopCounter(int sample_rate){
	*LETIMER0_TOP = 32768/sample_rate;
}

/* Function disables the low energy timer. 
 * Used to save energy when the timer
 * is not needed. It basically reverts
 * the changes by setupLowEnergyTimer()
 */

void disableLowEnergyTimer(){
	*CMU_OSCENCMD &= ~(1 << 6);
	*CMU_HFCORECLKEN0 &= (1 << 4);
	*LETIMER0_CTRL &= (1 << 9);
	*CMU_LFACLKEN0 &= (1 << 2);
	*LETIMER0_TOP = 0;
	*LETIMER0_IEN = 0;
	*LETIMER0_CMD = 0;
}
