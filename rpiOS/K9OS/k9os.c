
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
        function select 1:         0004 
	pin set 1        :         001C 
	pin clear 1      :         0028 	

   There are different addresses for SET and CLEAR because (?) 
   (page 95 of BCM manual):
   "Separating the set and clear functions removes the need for 
   read-modify-write operations."
*/

#define GPIO_BASE  0x20200000UL
#define SPEED      500000
/* volatile registers: */

/* prepare led registers for IO: */
volatile unsigned int* led_prep;  /* function select 1 */
volatile unsigned int* led_clear; /* pin clear 1 */
volatile unsigned int* led_set;   /* pin set 1 */

/* loop variable. Volatile because the loops where it appears do 
   nothing than keep the program from crashing?  */
volatile unsigned int t;

/* compiler creates no entry/exit code. Registers directly accessed(?):
*/
int main(void) __attribute__((naked));
 
int main(void)
{
  led_prep  = (unsigned int*)(GPIO_BASE + 0x4);
  led_clear = (unsigned int*)(GPIO_BASE + 0x28);
  led_set   = (unsigned int*)(GPIO_BASE + 0x1c); 
  
  /*  This will ready the GPIO16 pin for output. */
  *led_prep |= (1<<18);
  
  while(1)
    {
      for(t=0; t<SPEED; t++)
	;
      *led_clear |= (1<<16); /* turn on */
      
      for(t=0; t<SPEED; t++)
	;
      *led_set |= (1<<16);  /* turn off */
    }
}
