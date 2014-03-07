#include <stdint.h>
#include <stdbool.h>

#include "efm32gg.h"
#include "sounds.h"

extern struct tone *sampleArray;
extern int songlength;

void disableLowEnergyTimer();
void disableDAC();
//int pos=0;

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
//	*GPIO_IFC = *GPIO_IF;
	
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
	playSong(sampleArray, songlength);

}


