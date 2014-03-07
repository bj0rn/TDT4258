#include <stdint.h>
#include <stdbool.h>

#include "efm32gg.h"
#include "sounds.h"

extern struct tone *sampleArray;
extern int songlength;
extern int runBattlefield;

void disableLowEnergyTimer();
void disableDAC();



/* TIMER1 interrupt handler */

void __attribute__ ((interrupt)) TIMER1_IRQHandler() 
{  
	*TIMER1_IFC = 1;	
  /*
    TODO feed new samples to the DAC
    remember to clear the pending interrupt by writing 1 to TIMER1_IFC
  */

}

/* GPIO even pin interrupt handler */
void __attribute__ ((interrupt)) GPIO_EVEN_IRQHandler() 
{
	/* Clear pending interrupts */
	
	select_melodies();
	
	*GPIO_IFC = 0xff;
	*GPIO_PA_DOUT = (*GPIO_PC_DIN << 8);
  

}

/* GPIO odd pin interrupt handler */
void __attribute__ ((interrupt)) GPIO_ODD_IRQHandler() 
{
	*GPIO_IFC = 0xff;
	select_melodies();
	*GPIO_PA_DOUT = (*GPIO_PC_DIN << 8);

}

void __attribute__ ((interrupt)) LETIMER0_IRQHandler(){
	
	*LETIMER0_IFC = 1;


	/* Feed new samples to the DAC */
	if(runBattlefield){
		play_music(songlength);
	}else {
		playSong(sampleArray, songlength);
	}
	

}


