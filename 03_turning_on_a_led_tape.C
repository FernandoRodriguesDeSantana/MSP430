#include <msp430.h>

void main(void)
{
    WDTCTL = WDTPW | WDTHOLD;       // Para o watchdog timer
    P1DIR = 0b00000001;             // Definindo P1.0 como saída e P1.1 como entrada
    P1REN |= 0b00000010;            // Habilitando o resistor em P1.1
    P1OUT |= 0b00000010;            // Escolhendo pull-up em P1.1

    P2DIR = 0b00010000;             // Definindo P2.5 como saída
    P2OUT &= ~0b00010000;           // Garantindo que P2.5 irá iniciar sem tensão

    while(1)
    {
     if((P1IN & 0b00000010) == 0)
     {
         P1OUT |= 0b00000001;       // Acende LED1
         P2OUT |= 0b00010000;       // Acende fita
     }
     else
     {
         P1OUT &= ~0b00000001;      // Apaga LED
         P2OUT &= ~0b00010000;      // Apaga fita
     }
    }

    return 0;
}
