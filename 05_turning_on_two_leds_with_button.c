#include <msp430.h>

void main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // para watchdog timer
    P1DIR = BIT0;               // definindo P1.0 como saída e P1.1 como entrada
    P1REN |= BIT1;              // habilitando pull-up e pull-down eM P1.1
    P1OUT |= BIT1;              // escolhendo pull-up em P1.1

    P4DIR = BIT7;

    while(1)
    {
     if((P1IN & BIT1) == 0)
     {
         P1OUT |= BIT0;         // acende o led em P1.0
         P4OUT |= BIT7;         // acende o led em P4.7
     }
     else
     {
         P1OUT &= ~BIT0;        // apaga o led em P1.0
         P4OUT &= ~BIT7;        // apaga o led em P4.7
     }
    }
    return 0;
}
