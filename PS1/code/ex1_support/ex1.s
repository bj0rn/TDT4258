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

	/////////////////////////////////////////////////////////////////////////////
	//
	// Reset handler
  // The CPU will start executing here after a reset
	//
	/////////////////////////////////////////////////////////////////////////////

	      .globl  _reset
	      .type   _reset, %function
        .thumb_func
_reset: 
	      BL setup_gpio_clk
	      BL setup_leds
	      BL setup_buttons
	      BL setup_interrupts
		  BL setup_energy_mode
		 // BL polling
          WFI
		  B . //just in case
          
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

		.thumb_func
setup_leds:
		//load gpio pa base address
		ldr r1, =GPIO_PA_BASE
		
		//set high drive strength
		mov r2, #0x2
		str r2, [r1]
		
		//set pins 8-15 output
		ldr r2, gpio_output
		str r2, [r1, #GPIO_MODEH]

	   //set pins high
	   // mov r2, #0xff
	   // lsl r2, r2, #8
   	   // str r2, [r1, #GPIO_DOUT]

		BX LR

		.thumb_func
setup_buttons:
		ldr r1, =GPIO_PC_BASE 
 		ldr r2, gpio_input
		str r2, [r1, #GPIO_MODEL]
		mov r2, #0xff
		str r2, [r1, #GPIO_DOUT]

		BX LR

	  .thumb_func
setup_energy_mode: 
		ldr r1, =SCR
		mov r2, #6
		str r2, [r1]
       
	    BX LR


	  .thumb_func
polling:
		ldr r1, =GPIO_PC_BASE
		ldr r2, =GPIO_PA_BASE
while: 	
		ldr r3, [r1, #GPIO_DIN]
		lsl r3, r3, #8
		str r3, [r2, #GPIO_DOUT]
		b while

	.thumb_func
setup_interrupts:
	  //LOAD GPIO base
	  ldr r1, =GPIO_BASE
	 
	 //Load interrupt enable value
	  ldr r2, gpio_pc_interrupt
	 
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
	 ldr r2, enable_interrupt_handling
	 str r2, [r1]
	 
	 BX LR



enable_interrupt_handling:
		.word 0x802


gpio_pc_interrupt:
		.word 0x22222222

gpio_output:
			.word 0x55555555

gpio_input: 
			.word 0x33333333




	




/////////////////////////////////////////////////////////////////////////////
	//
  // GPIO handler
  // The CPU will jump here when there is a GPIO interrupt
	//
	/////////////////////////////////////////////////////////////////////////////
	
        .thumb_func
gpio_handler:  
		//Clear interrupt handler
		ldr r1, =GPIO_BASE
		mov r2, #0xff
		str r2, [r1, #GPIO_IFC]
		
        //Turn on buttons
		ldr r1, =GPIO_PC_BASE
	    ldr r2, =GPIO_PA_BASE

	    ldr r3, [r1, #GPIO_DIN]
	    lsl r3, r3, #8
		str r3, [r2, #GPIO_DOUT]
        
		BX LR
		NOP 
	
	
	/////////////////////////////////////////////////////////////////////////////

	.thumb_func
delay:
	movw r3, #0xFFFF
	movt r3, #0x0000
delay_loop:
	cbz r3, delay_exit
	sub r3, r3, #1
	B delay_loop
delay_exit:
	BX LR


        .thumb_func
dummy_handler:  
     b .  // do nothing

