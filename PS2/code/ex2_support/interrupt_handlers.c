#include <stdint.h>
#include <stdbool.h>

#include "efm32gg.h"
#include "sounds.h"
#include "melodies.h"

extern int tone;
//int test[] = {A,B,C,D,E,F,E,D,C,B,A,B,C,D,E,F,E,D,C,B,A,SILENCE};
int pos=0;

//struct tone t1 = {A, 100000};
//struct tone t2 = {B, 50000};
//struct tone t3 = {C, 20000};

/* TIMER1 interrupt handler */

void __attribute__ ((interrupt)) TIMER1_IRQHandler() 
{  
	*TIMER1_IFC = 1;	
  /*
    TODO feed new samples to the DAC
    remember to clear the pending interrupt by writing 1 to TIMER1_IFC
  */
	
    testNotes(mario[pos].note, mario[pos].time);
     if(iterate==true){
        pos++;
        iterate=false;
        *GPIO_PA_DOUT = (pos << 8);
     }else if(pos > 33){
		 //disableTimer();
	 }

//  testNotes(test[3], 100000);
//  testNotes(test[0], 100000);
//  *GPIO_PA_DOUT = (0xff<<8);
  
   
}

/* GPIO even pin interrupt handler */
void __attribute__ ((interrupt)) GPIO_EVEN_IRQHandler() 
{
	/* Clear pending interrupts */
	*GPIO_IFC = *GPIO_IF;
	//*GPIO_IFC = 0xff;

	
	//*GPIO_PA_DOUT = (*GPIO_PC_DIN << 8);
  	*GPIO_PA_DOUT = 0x0;		
	//while((*GPIO_PC_DIN)!=0xff){
	//	play_piano();
		//testNotes(A, 50000);	
	//}
//	 play_music(test, 6, 0);
//




    /* TODO handle button pressed event, remember to clear pending interrupt */
}

/* GPIO odd pin interrupt handler */
void __attribute__ ((interrupt)) GPIO_ODD_IRQHandler() 
{
	/*Clear pending interrupts*/
	*GPIO_IFC = *GPIO_IF;
	

	*GPIO_PA_DOUT = (0xff << 8);


//	*GPIO_IFC = 0xff;
	
	//*GPIO_PA_DOUT = (*GPIO_PC_DIN << 8);
	
	//while((*GPIO_PC_DIN)!=0xff){
//		testNotes(A, 50000);	
	//	play_piano();
	// }	 

   /* TODO handle button pressed event, remember to clear pending interrupt */
	/* TODO set input and output pins for the joystick */

}

void __attribute__ ((interrupt)) LETIMER0_IRQHandler(){
	//play_music(192000, 0);
	*GPIO_PA_DOUT = (0x0f<<8);
	//Clear interrupt
	*LETIMER0_IFC = 1;

}

