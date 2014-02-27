#include <stdint.h>
#include <stdbool.h>

#include "efm32gg.h"
#include "sounds.h"

extern int tone;
int test[] = {A, B, C, D, E, F, E,D,C,B,A, SILENCE};
int pos=0;


/* TIMER1 interrupt handler */

void __attribute__ ((interrupt)) TIMER1_IRQHandler() 
{  
	
  /*
    TODO feed new samples to the DAC
    remember to clear the pending interrupt by writing 1 to TIMER1_IFC
  */
//  *GPIO_PA_DOUT = (0xff<<8);
//  *TIMER1_IFC=1;
//  play_music(192000, 0);
//  play_note(tone);
//  play_music(test, 6, 0);
     testNotes(test[pos], 100000);
     if(iterate==true){
        pos++;
        iterate=false;

     }
//  testNotes(test[3], 100000);
//  testNotes(test[0], 100000);
//  *GPIO_PA_DOUT = (0xff<<8);
	*TIMER1_IFC=1;
  
   
}

/* GPIO even pin interrupt handler */
void __attribute__ ((interrupt)) GPIO_EVEN_IRQHandler() 
{
	/* Clear pending interrupts */
//	*GPIO_IFC = *GPIO_IF;
	*GPIO_IFC = 0xff;
	
	
//	*GPIO_PA_DOUT = (*GPIO_PC_DIN << 8);
	*GPIO_PA_DOUT = (0xff << 8);
//	 play_music(test, 6, 0);


    /* TODO handle button pressed event, remember to clear pending interrupt */
}

/* GPIO odd pin interrupt handler */
void __attribute__ ((interrupt)) GPIO_ODD_IRQHandler() 
{
	/*Clear pending interrupts*/
//	*GPIO_IFC = *GPIO_IF;
	*GPIO_IFC = 0xff;
		    
//	*GPIO_PA_DOUT = (*GPIO_PC_DIN << 8);
	*GPIO_PA_DOUT = (0x00 << 8);		    


    /* TODO handle button pressed event, remember to clear pending interrupt */
	/* TODO set input and output pins for the joystick */
}
