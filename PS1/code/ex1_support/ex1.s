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
	      DELAY = 2500
	      BL setup_gpio_clk

//	      ldr r1, =CMU_BASE
//	      mov r2, #9

//	      str r2, [r1, #CMU_HFPERCLKDIV]	      

	      BL setup_leds
	      BL setup_buttons
<<<<<<< HEAD
		  BL convert_to_ms
=======
//		  BL wave_left
//		  BL blink
>>>>>>> f0d90fde020d5d7986cf333353f97159ac7e6513
//	      BL powerdown_ram3
          BL setup_interrupts
          BL setup_energy_mode
	      
//	      BL polling
<<<<<<< HEAD
//             WFI

      
 
=======
            WFI
          
>>>>>>> f0d90fde020d5d7986cf333353f97159ac7e6513
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
		ldr r2, =0x55555555
		str r2, [r1, #GPIO_MODEH]

	   //set pins high
	   // mov r2, #0xff
	   // lsl r2, r2, #8
   	   // str r2, [r1, #GPIO_DOUT]

		BX LR

		.thumb_func
setup_buttons:
		ldr r1, =GPIO_PC_BASE 
 		ldr r2, =0x33333333
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
convert_to_ms:

	ldr r5, =DELAY
	ldr r3, =5000
	mul r6, r5, r3
//	DELAY_MS = r6

	.thumb_func
blink:
	ldr r1, =GPIO_PA_BASE
	
while_loop:
	mov r2, #0x0f
	mov r4, #0xf0
	lsl r2, r2, #8
	lsl r4, r4, #8
	str r2, [r1, #GPIO_DOUT]
	BL delay
	str r4, [r1,#GPIO_DOUT]
	BL delay
	B while_loop

	.thumb_func
wave_left:
	mov r12, lr
	ldr r1, =GPIO_PA_BASE
	ldr r2, =GPIO_PC_BASE
	ldr r3, [r2, #GPIO_DIN] 
	mov r4, #0xff
	eor r5, r3, r4
	mov r9, #0

light:
	eor r3, r5, r3
    BL delay 
	lsl r11, r3, #8
	str r11, [r1, #GPIO_DOUT]
	BL delay
	lsr r5, r5, #1
	cmp r9, r5
	bne light

	BX r12






	.thumb_func
delay:
<<<<<<< HEAD
	mov r3, r6
	mov r7, lr
=======
	push {r6}
	ldr r6, =0x000fffff
>>>>>>> f0d90fde020d5d7986cf333353f97159ac7e6513
do_wait: 
	subs r3, #1
	bne do_wait
	pop {r6}
	BX lr


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
	    ldr r2, [r1, #GPIO_IF]
	    str r2, [r1, #GPIO_IFC]
		
        //Turn on buttons
	   // ldr r1, =GPIO_PC_BASE
	   // ldr r2, =GPIO_PA_BASE

	   // ldr r3, [r1, #GPIO_DIN]
	   // lsl r3, r3, #8
	   // str r3, [r2, #GPIO_DOUT]
        push {lr}
	    BL wave_left
        NOP
		pop {lr}
	    BX LR	
	
	/////////////////////////////////////////////////////////////////////////////
	.thumb_func
powerdown_ram3:
	ldr r1, =EMU_BASE
	mov r2, #4
	
	str r2, [r1, #EMU_MEMCTRL]
	BX LR		
	

        .thumb_func
dummy_handler:  
     b .  // do nothing

