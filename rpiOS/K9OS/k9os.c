
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

volatile unsigned int* gpio = (unsigned int*)GPIO_BASE; /*   */
  
/* loop variable. Volatile because any optimisation above -O0 removes the loop where this appears. */
volatile unsigned int t;

/* compiler creates no entry/exit code. */
int main(void) __attribute__((naked));
 
int main(void)
{
  /*  This will ready for output the pin GPIO16, controlled by the
      6th set of 3 bits, of the 1st (0x4>>2) int-sized-chunk after
      gpio. */
  (0x4>>2)[gpio] |= (1<<18);
  
  while(1)
    {
      for(t=0; t<SPEED; t++)
	;
      (0x28>>2)[gpio] |= (1<<16); /* turn on */
      
      for(t=0; t<SPEED; t++)
	;
      (0x1c>>2)[gpio] |= (1<<16);  /* turn off */
    }
}
