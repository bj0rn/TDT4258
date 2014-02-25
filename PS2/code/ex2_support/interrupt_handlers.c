#include <stdint.h>
#include <stdbool.h>

#include "efm32gg.h"
#include "sounds.h"

int value = 0;

/* TIMER1 interrupt handler */
void __attribute__ ((interrupt)) TIMER1_IRQHandler() 
{  
  /*
    TODO feed new samples to the DAC
    remember to clear the pending interrupt by writing 1 to TIMER1_IFC
  */
  testNotes(48000);

  *GPIO_PA_DOUT = (0xff<<8);
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
