        .syntax unified
	
	      .include "efm32gg.s"

	/////////////////////////////////////////////////////////////////////////////
	//
  // Exception vector table
  // This table contains addresses for all exception handlers
	//
	/////////////////////////////////////////////////////////////////////////////
	
        .section .vectors
	
	      .long   stack_top               /* Top of Stack                 */
	      .long   _reset                  /* Reset Handler                */
	      .long   dummy_handler           /* NMI Handler                  */
	      .long   dummy_handler           /* Hard Fault Handler           */
	      .long   dummy_handler           /* MPU Fault Handler            */
	      .long   dummy_handler           /* Bus Fault Handler            */
	      .long   dummy_handler           /* Usage Fault Handler          */
	      .long   dummy_handler           /* Reserved                     */
	      .long   dummy_handler           /* Reserved                     */
	      .long   dummy_handler           /* Reserved                     */
	      .long   dummy_handler           /* Reserved                     */
	      .long   dummy_handler           /* SVCall Handler               */
	      .long   dummy_handler           /* Debug Monitor Handler        */
	      .long   dummy_handler           /* Reserved                     */
	      .long   dummy_handler           /* PendSV Handler               */
	      .long   dummy_handler           /* SysTick Handler              */

	      /* External Interrupts */
	      .long   dummy_handler
	      .long   gpio_handler            /* GPIO even handler */
	      .long   dummy_handler
	      .long   dummy_handler
	      .long   dummy_handler
	      .long   dummy_handler
	      .long   dummy_handler
	      .long   dummy_handler
	      .long   dummy_handler
	      .long   dummy_handler
	      .long   dummy_handler
	      .long   gpio_handler            /* GPIO odd handler */
	      .long   dummy_handler
	      .long   dummy_handler
	      .long   dummy_handler
	      .long   dummy_handler
	      .long   dummy_handler
	      .long   dummy_handler
	      .long   dummy_handler
	      .long   dummy_handler
	      .long   dummy_handler
	      .long   dummy_handler
	      .long   dummy_handler
	      .long   dummy_handler
	      .long   dummy_handler
	      .long   dummy_handler
	      .long   dummy_handler
	      .long   dummy_handler
	      .long   dummy_handler
	      .long   dummy_handler
	      .long   dummy_handler
	      .long   dummy_handler
	      .long   dummy_handler
	      .long   dummy_handler
	      .long   dummy_handler
	      .long   dummy_handler
	      .long   dummy_handler
	      .long   dummy_handler
	      .long   dummy_handler

	      .section .text

	////////////////////////////////////////////////////////////////////////////
	//																		  //	
	// Reset handler														  //	
    // The CPU will start executing here after a reset						  //
	//																		  //	
	////////////////////////////////////////////////////////////////////////////

	      .globl  _reset
	      .type   _reset, %function
        .thumb_func
_reset:
	      DELAY = 150
	      BL setup_gpio_clk

//	      ldr r1, =CMU_BASE
//	      mov r2, #9
//	      str r2, [r1, #CMU_HFPERCLKDIV]	      

	      BL setup_leds
	      BL setup_buttons
	      BL convert_to_ms
		  BL blink
//	      BL powerdown_ram3
          BL setup_interrupts
          BL setup_energy_mode
	      
//	      BL polling
          WFI


	////////////////////////////////////////////////////////////////////////////
	//																	      //		
	// Enable GPIO_CLOCK													  //	
	//																		  //	
	////////////////////////////////////////////////////////////////////////////
          
	     .thumb_func
setup_gpio_clk:
		 //Load CMU base address
		 ldr r1, =CMU_BASE

		 //load current value of HFPERCLK ENBALE
		 ldr r2, [r1, #CMU_HFPERCLKEN0]

		 //Set bit for GPIO clk
		 mov r3, #1 
		 lsl r3, r3, #CMU_HFPERCLKEN0_GPIO
		 orr r2, r2, r3

		 //Store new value 
		 str r2, [r1, #CMU_HFPERCLKEN0]
		
		 BX LR


	///////////////////////////////////////////////////////////////////////////
	//																	     //		
	// Confifure the gamepad LEDs											 //
	//																		 //
	///////////////////////////////////////////////////////////////////////////

		.thumb_func
setup_leds:
		//load gpio pa base address
		ldr r1, =GPIO_PA_BASE
		
		//set high drive strength
		mov r2, #0x2
		str r2, [r1, #GPIO_CTRL]
		
		//set pins 8-15 output
		ldr r2, =0x55555555
		str r2, [r1, #GPIO_MODEH]

		BX LR

	//////////////////////////////////////////////////////////////////////////
	//																		//
	//Configure gamepad buttons												//
	//																		//
	//////////////////////////////////////////////////////////////////////////
		.thumb_func
setup_buttons:
		//Load GPIO_PC_BASE
		ldr r1, =GPIO_PC_BASE 
 		
		//Set pins 0-7 to input
		ldr r2, =0x33333333
		str r2, [r1, #GPIO_MODEL]
		
		//Enable interal pull-up
		mov r2, #0xff
		str r2, [r1, #GPIO_DOUT]

		BX LR

	/////////////////////////////////////////////////////////////////////////
	//																	   //	
	// Configure deepsleep mode											   //	
	//																	   //	
	/////////////////////////////////////////////////////////////////////////


	  .thumb_func
setup_energy_mode: 
		//Load the system control register
		ldr r1, =SCR
		
		//Configure deepsleep and deepsleep on exit
		mov r2, #6
		str r2, [r1]
		BX LR
	

	////////////////////////////////////////////////////////////////////////
	//																	  //	
	// Convert to milliseconds											  //
	//																	  //	
	////////////////////////////////////////////////////////////////////////


	.thumb_func
convert_to_ms:

	ldr r5, =DELAY //DELAY-variable specified in milliseconds
	ldr r3, =5000
	mul r6, r5, r3
	BX LR

	///////////////////////////////////////////////////////////////////////
	//																	 //
	// Blink effect														 //
	//																	 //
	///////////////////////////////////////////////////////////////////////

	.thumb_func
blink:
	ldr r1, =GPIO_PA_BASE
	
while_loop:
	mov r2, #0x0f
	mov r4, #0xf0
	lsl r2, r2, #8
	lsl r4, r4, #8
	str r2, [r1, #GPIO_DOUT] //r1 is loaded with GPIO_PA_BASE
	BL delay
	str r4, [r1,#GPIO_DOUT]
	BL delay
	B while_loop


	/////////////////////////////////////////////////////////////////////
	//																   //	
	// Wave effect													   //	
	//																   //	
	/////////////////////////////////////////////////////////////////////
	

	.thumb_func
wave_left:
	mov r12, lr
	ldr r1, =GPIO_PA_BASE
	ldr r2, =GPIO_PC_BASE
	ldr r8, [r2, #GPIO_DIN] 
	mov r4, #0xff
	eor r5, r8, r4
	lsr r5, r5, #1
	mov r9, #0

light:
	eor r8, r5, r8
    ldr r6, =375000
	BL delay 
	lsl r11, r8, #8
	str r11, [r1, #GPIO_DOUT]
	BL delay
	lsr r5, r5, #1
	cmp r9, r5
	bne light
    
    
	ldr r6, =750000
	lsl r9, r9, #8
	str r9, [r1, #GPIO_DOUT]
	BL delay
	lsl r4, r4, #8
	str r4, [r1, #GPIO_DOUT]
	BL delay
	BX r12

	///////////////////////////////////////////////////////////////////
	//																 //	
	// Delay function												 //
	//																 //
	///////////////////////////////////////////////////////////////////

	.thumb_func
delay:
	mov r3, r6
	mov r7, lr
do_wait: 
	subs r3, #1
	bne do_wait
	BX lr

	//////////////////////////////////////////////////////////////////
	//																//
	// Polling function												//
	//																//
	//////////////////////////////////////////////////////////////////



	  .thumb_func
polling:
		ldr r1, =GPIO_PC_BASE
		ldr r2, =GPIO_PA_BASE
while: 	
		ldr r3, [r1, #GPIO_DIN]
		lsl r3, r3, #8
		str r3, [r2, #GPIO_DOUT]
		b while

	///////////////////////////////////////////////////////////////////
	// 																 //	
	// Configure interrupts for gamepad buttons						 //			
	//																 //	
	///////////////////////////////////////////////////////////////////


	.thumb_func
setup_interrupts:
	  //LOAD GPIO base
	  ldr r1, =GPIO_BASE
	 
	 //Load interrupt enable value
	  ldr r2, =0x22222222 //gpio_output
	 
	 //Store value
	  str r2, [r1, #GPIO_EXTIPSELL]
	 
	 //Setup interrupt falling edge
	  mov r2, #0xff
	  str r2, [r1, #GPIO_EXTIFALL]
	 
	 //setup interrupt on rising edge
	  mov r2, #0xff
	  str r2, [r1, #GPIO_EXTIRISE]
	  
	 //Enable interrupt generation
	  mov r2, #0xff
	  str r2, [r1, #GPIO_IEN]

     //Enable interrupt handling
    	 ldr r1, =ISER0
	 ldr r2, =0x802 //enable_interrupt_handling
	 str r2, [r1]
	 
	 BX LR

	////////////////////////////////////////////////////////////////////
	//																  //
 	// GPIO handler													  //	
  	// The CPU will jump here when there is a GPIO interrupt		  //	
	//																  //
	////////////////////////////////////////////////////////////////////
	
        .thumb_func
gpio_handler:  
		//Clear interrupt handler
	    ldr r1, =GPIO_BASE
	    ldr r2, [r1, #GPIO_IF]
	    str r2, [r1, #GPIO_IFC]
		
        //Turn on buttons
	    ldr r1, =GPIO_PC_BASE
	    ldr r2, =GPIO_PA_BASE

		ldr r3, [r1, #GPIO_DIN]
	    lsl r3, r3, #8
	    str r3, [r2, #GPIO_DOUT]
		push {lr}
	    BL wave_left
	    pop {lr}
	    
		BX LR	
	
	///////////////////////////////////////////////////////////////////
	//																 //	
	//Power down ram block 3										 //
	//																 //
	///////////////////////////////////////////////////////////////////
		
		.thumb_func
powerdown_ram3:
	ldr r1, =EMU_BASE
	mov r2, #4
	
	str r2, [r1, #EMU_MEMCTRL]
	BX LR		
	

        .thumb_func
dummy_handler:  
     b .  // do nothing

