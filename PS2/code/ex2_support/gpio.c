#include <stdint.h>
#include <stdbool.h>

#include "efm32gg.h"

/* function to set up GPIO mode and interrupts*/
void setupGPIO()
{
	*CMU_HFPERCLKEN0 |= (1 << 13); /* Enable GPIO clock*/
  	
	/*Configure gamepad LEDs*/
	*GPIO_PA_CTRL = 2; /* Set high drive strength */
	*GPIO_PA_MODEH = 0x55555555; /*Set pins A8-15 as output*/
	
	/*Configure gamepad buttons */
	*GPIO_PC_MODEL = 0x33333333; /*Set pins C0-7 as input*/
	*GPIO_PC_DOUT = 0xff; /*Enable internal pull-up*/

	/* Configure interrupts */
	*GPIO_EXTIPSELL = 0x22222222; /*Enable interrupts*/
	*GPIO_EXTIFALL = 0xff; /*Sense falling edge */
	*GPIO_EXTIRISE = 0xff; /*Sense rising edge */
	*GPIO_IEN = 0xff; /*Enable interrupt generation*/
	*ISER0 = 0x802; /*Enable interrupt handling*/

	/*Configure deepsleep mode */
	*SRC = 6; /* Set the DEEPSLEEP bit and the SLEEPONEXIT bit  */


    
  /* Example of HW access from C code: turn on joystick LEDs D4-D8
     check efm32gg.h for other useful register definitions
  */
  //*GPIO_PA_DOUT = 0x0700; /* turn on LEDs D4-D8 (LEDs are active low) */
}



