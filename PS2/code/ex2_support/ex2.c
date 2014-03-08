#include <stdint.h>
#include <stdbool.h>

#include "efm32gg.h"


/* 
  TODO calculate the appropriate sample period for the sound wave(s) 
  you want to generate. The core clock (which the timer clock is derived
  from) runs at 14 MHz by default. Also remember that the timer counter
  registers are 16 bits.
*/
/* The period between sound samples, in clock cycles */
#define SAMPLE_PERIOD 32748

/* Declaration of peripheral setup functions */
void setupTimer(uint32_t period);
void setupDAC();
void setupNVIC();
void setupLowEnergyTimer();
void setupGPIO();
void changeTopCounter(int sample_rate);
void initSound();

/* Your code will start executing here */
int main(void) {
	
	initSound(); /* Reset every global variable at reset */
  	setupGPIO(); /* Configure buttons and LEDs */
  	
	/* These functions are used called when needed. E.g when we play tunes. See
	 * sounds.c:selectMelodies() */
	
	//setupDAC();
  	//setupLowEnergyTimer();
    //setupTimer(48000);


 	setupNVIC(); /*Setup exceptions vectors*/

 	*SCR = 6; /* Set the DEEPSLEEP bit and the SLEEPONEXIT bit  */

    __asm("WFI"); /* Wait for interrupts */


  	while(1){}

  	return 0;
}

void setupNVIC()
{
	 *ISER0 = 0x4000802;
}

