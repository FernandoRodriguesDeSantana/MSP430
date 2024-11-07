#include <msp430.h> 

int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	
	P1DIR = 0x00000001; // define P1.0 (LED) como saída
	P1OUT = 0x00000001; // P1.0 é colocada em nível lógico alto (ACENDE O LED)

	return 0;
}
