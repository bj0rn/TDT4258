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
	initSound();
  	setupGPIO();
  	setupDAC();
  	setupLowEnergyTimer();
    
  	changeTopCounter(8000);



  /* Enable interrupt handling */
  setupNVIC();

  /* TODO for higher energy efficiency, sleep while waiting for interrupts
     instead of infinite loop for busy-waiting
  */

  /* Wait for interrupts */
  *SCR = 6; /* Set the DEEPSLEEP bit and the SLEEPONEXIT bit  */

  __asm("WFI");


  while(1){ 
	//__asm("WFI");
  }

  return 0;
}

void setupNVIC()
{
	 *ISER0 = 0x4000802;
}

