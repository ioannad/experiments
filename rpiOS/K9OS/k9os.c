
/* The base address of the ARM physical address, 
   the GPIO peripheral, and the extra bits to the needed
   registers. Information provided in the BCM2835-ARM-Peripherals 
   manual, and the wiring diagram of the RPi. 

   VC CPU Address 0x7E000000 |--> ARM Physical Address 0x20000000 
   (BCM2835 Arms Peripheral manual section 1.2.3.)
				  
   OK LED wired to GPIO16 (Raspberry Pi R2.0 schematics, pg2, 
   chess-block B5)

   BCM manual: "The FSEL{n} field determines the functionality of the 
   (page 91)    nth GPIO pin. All unused alternative function lines are
		tied to ground and will output a “0” if selected. All 
		pins reset to normal GPIO input operation."

   GPIO16 then is controlled by FSEL16, thus bits 20-18 of the GPIO's
   Function Select 1 (Table 6-3, page 92).
   
   GPIO smallest address : 0x 7E20 0000 |--> 0x 2020 0000
        function select 1: 0x 7E20 0004 |-->        +0x04
	pin set 1        : 0x 7E20 0020 |-->        +0x20
	pin clear 1      : 0x 7E20 002C |-->        +0x2C	
*/

#define GPIO_BASE  0x20200000UL

/* volatile registers: */

/* prepare led registers for IO: GPIO Function Select 1 (page 90) */
volatile unsigned int* led_prep;
volatile unsigned int* led_clear;
volatile unsigned int* led_set;

/* loop variable. Volatile because the loops where it appears do 
   nothing than keep the program from crashing?  */
volatile unsigned int t;


/* Provides necessary _main symbol. */

int main(void)
{
  led_prep  = (unsigned int*)(GPIO_BASE + 4);
  led_clear = (unsigned int*)(GPIO_BASE + 40); /* = +0x2c */
  
  /* Set bit 18 of register LED_SELECT to 1. 
     This will ready the GPIO16 pin for output. */
  *led_prep |= (1<<18);

  for(t=0; t<5000; t++)
	;
  
  /* To light the LED, output a 0 on bit 16 of the CLEAR 
     register of GPIO. This is done by setting the 
     gpio_clear register's 16th bit to 1.*/
  while(1)
    {
      for(t=0; t; t++)
	;
      *led_clear |= (1<<16);
      
    }
  return 0;
}

/* Provides necessary _exit symbol. Normally a system call when a 
   program terminates. Not necessary for now, as there are no 
   programs to be run except this one.  */
void exit(int code)
{
  while(1); /* Important to have an infinite loop: the C library
               we use is not to be used with an OS (-none-), so 
	       there `exit` is marked as noreturn. A return would
	       cause a warning. */
}
