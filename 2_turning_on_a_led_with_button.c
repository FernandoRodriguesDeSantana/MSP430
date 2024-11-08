#include <msp430.h>

void main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // para watchdog timer
    P1DIR = 0b00000001;         // definindo P1.0 como saída e P1.1 como entrada
    P1REN |= 0b00000010;        // habilitando pull-up e pull down e P1.1
    P1OUT |= 0b00000010;        // escolhendo pull-up em P1.1

    while(1)
    {
     if((P1IN & 0b00000010) == 0)
     {
         P1OUT |= 0b00000001;
     }
     else
     {
         P1OUT &= ~0b00000001;
     }
    }
    return 0;
}
