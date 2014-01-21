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
		 ////// BL polling
          
		  B .
          
		.thumb_func
setup_gpio_clk:
		 //Load CPU base address
		 ldr r1, cmu_base_addr

		 //load current value of HFPERCLK ENBALE
		 ldr r2, [r1, #CMU_HFPERCLKEN0]

		 //Set bit for GPIO clk
		 mov r3, #1 
		 lsl r3, r3, #CMU_HFPERCLKEN0_GPIO
		 orr r2, r2, r3

		 //Store new value 
		 str r2, [r1, #CMU_HFPERCLKEN0]

		.thumb_func
setup_leds:
		//load gpio pa base address
		ldr r1, gpio_pa_base_addr
		
		//set high drive strength
		mov r2, #0x2
		str r2, [r1]
		
		//set pins 8-15 output
		ldr r2, gpio_output
		str r2, [r1, #GPIO_MODEH]

		//set pins high
	   // mov r2, #0xff
		//lsl r2, r2, #8
   		//str r2, [r1, #GPIO_DOUT]

		.thumb_func
setup_buttons:
		ldr r1, gpio_pc_base_addr
 		ldr r2, gpio_input
		str r2, [r1, #GPIO_MODEL]
		mov r2, #0xff
		str r2, [r1, #GPIO_DOUT]



	  .thumb_func
polling:
		ldr r1, gpio_pc_base_addr
		ldr r2, gpio_pa_base_addr
while: 	
		ldr r3, [r1, #GPIO_DIN]
		//mov r3, 0xDF
		lsl r3, r3, #8
		str r3, [r2, #GPIO_DOUT]
		b while

	.thumb_func
setup_interrupts:
	  //LOAD base address for port C
	  ldr r1, gpio_pc_base_addr
	 
	 //Load interrupt enable value
	  ldr r2, gpio_pc_interrupt
	 
	 //Store value
	  ldr r2, [r1, #GPIO_EXTIPSELL]
	 
	 //Setup interrupt falling edge
	  mov r2, #0xff
	  str r2, [r1, GPIO_EXTIFALL]
	 
	 //setup interrupt on rising edge
	  mov r2, #0xff
	  str r2, [r1, GPIO_EXTIRISE]
	  
	 //Enable interrupt generation
	  mov r2, #0xff
	  str r2, [r1, GPIO_IEN]

     //Enable interrupt handling
     ldr r1, iser0
	 ldr r2, enable_interrupt_handling
	 str r2, [r1]
	  

enable_interrupt_handling:
		.word 0x802

iser0: 
	   .word ISER0

gpio_pc_interrupt:
		.word 0x22222222

gpio_output:
			.word 0x55555555

gpio_input: 
			.word 0x33333333

gpio_pa_base_addr:
			.long GPIO_PA_BASE

gpio_pc_base_addr:
			.long GPIO_PC_BASE

cmu_base_addr: 
			.long CMU_BASE



	




/////////////////////////////////////////////////////////////////////////////
	//
  // GPIO handler
  // The CPU will jump here when there is a GPIO interrupt
	//
	/////////////////////////////////////////////////////////////////////////////
	
        .thumb_func
gpio_handler:  
		 ldr r1, gpio_pa_base_addr
		 ldr r2, gpio_pc_base_addr
	     
		 ldr r3, [r2, #GPIO_DIN]
		 lsl r3, r3, #8
		 str r3, [r1, #GPIO_DOUT]

         mov r3, #0xff
		 str r3, [r2, GPIO_IFC]

	    //  b .  // do nothing
	
	/////////////////////////////////////////////////////////////////////////////
	
        .thumb_func
dummy_handler:  
       // b .  // do nothing

