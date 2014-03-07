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
	
//    testNotes(mario[pos].note, mario[pos].time);
//    if(iterate==true){
//       pos++;
//        iterate=false;
//        *GPIO_PA_DOUT = (pos << 8);
//     }else if(pos > 33){
		 //disableTimer();
//	 }
//	 *GPIO_PA_DOUT = (*DAC0_CH0DATA<<8);  
}

/* GPIO even pin interrupt handler */
void __attribute__ ((interrupt)) GPIO_EVEN_IRQHandler() 
{
	/* Clear pending interrupts */
//	*GPIO_IFC = *GPIO_IF;
//	*GPIO_IFC = 0xff;
	
	//*GPIO_PA_DOUT = (*GPIO_PC_DIN << 8);
  	//*GPIO_PA_DOUT = 0x0;		
//	*GPIO_PA_DOUT = (*DAC0_CH0DATA<<8);
//	while((*GPIO_PC_DIN)!=0xff){
//		play_piano();
//	}
//	play_melodies();
	

    /* TODO handle button pressed event, remember to clear pending interrupt */
}

/* GPIO odd pin interrupt handler */
void __attribute__ ((interrupt)) GPIO_ODD_IRQHandler() 
{

	
	/*Clear pending interrupts*/
//	*GPIO_IFC = 0xff;
//	while((*GPIO_PC_DIN)!=0xff){
//		play_piano();
//	}	 
//	play_melodies();

   /* TODO handle button pressed event, remember to clear pending interrupt */
	/* TODO set input and output pins for the joystick */

}

void __attribute__ ((interrupt)) LETIMER0_IRQHandler(){
	//static int sample=0;
	//sample+=55;
	//if(sample>4095)
	//	sample-=4095;
//	*DAC0_CH0DATA=sample;
//	*DAC0_CH1DATA=sample;
	//testNotes(mario[pos].note, mario[pos].time);
     //if(iterate==true){
      //  pos++;
      //  iterate=false;
//        *GPIO_PA_DOUT = (*DAC0_CH0DATA<<8);
     //}else if(pos > 37){
	//	 disableLowEnergyTimer();
//		 disableDAC();
	// }
	playSong(sampleArray, songlength);

	//Clear interrupt
//	*LETIMER0_IFC = 1;
}


/*Helper methods*/
