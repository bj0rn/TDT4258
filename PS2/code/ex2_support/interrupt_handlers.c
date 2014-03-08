#include <stdint.h>
#include <stdbool.h>

#include "efm32gg.h"
#include "sounds.h"

extern struct tone *sampleArray;
extern int songlength;
extern int runBattlefield;

void disableLowEnergyTimer();
void disableDAC();
void playMario();



/* TIMER1 interrupt handler.
 * Obselete function. Were used
 * in previous versions of the 
 * program.
 *
 */

void __attribute__ ((interrupt)) TIMER1_IRQHandler() 
{  
	*TIMER1_IFC = 1;	
	
	playMario();
	playSong(sampleArray, songlength);

}

/* GPIO even pin interrupt handler
 * This function will call select melody
 * function which is responseble for
 * selecting songs. The songs will be 
 * selected based on the button pushed.
 *
*/

void __attribute__ ((interrupt)) GPIO_EVEN_IRQHandler() 
{
	/* Clear pending interrupts */
	
	select_melodies();
	
	*GPIO_IFC = 0xff;
	*GPIO_PA_DOUT = (*GPIO_PC_DIN << 8);
  

}

/* GPIO odd pin interrupt handler. 
 * This function will call select melody
 * function which is responseble for
 * selecting songs. The songs will be 
 * selected based on the button pushed.
 *
 */ 

void __attribute__ ((interrupt)) GPIO_ODD_IRQHandler() 
{
	*GPIO_IFC = 0xff;
	select_melodies();
	*GPIO_PA_DOUT = (*GPIO_PC_DIN << 8);

}

/* LETIMER0 interrupt handler.
 * The function will be called
 * every interrupt pushing
 * a new sample to the DAC
 *
 */

void __attribute__ ((interrupt)) LETIMER0_IRQHandler(){
	
	*LETIMER0_IFC = 1;


	/* Feed new samples to the DAC */
	if(runBattlefield){
		play_music(songlength);
	}else {
		playSong(sampleArray, songlength);
	}
	

}


