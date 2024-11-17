#include <msp430.h> 
#include "LCD.h"

int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer

    P3DIR = 0xFF;
    P6DIR = 0xFF;

    inic_LCD_4bits();
    P3OUT |= BIT4;

    cmd_LCD(0x80, 0);
    cmd_LCD('I', 1);
    cmd_LCD('F', 1);
    cmd_LCD('S', 1);
    cmd_LCD('C', 1);

    cmd_LCD(0x80,0);
    escreve_LCD("TESTE");

    P1REN |= BIT1;                            // Enable P1.4 internal resistance
    P1OUT |= BIT1;                            // Set P1.4 as pull-Up resistance
    P1IES &= ~BIT1;                           // P1.4 Lo/Hi edge
    P1IFG &= ~BIT1;                           // P1.4 IFG cleared
    P1IE |= BIT1;                             // P1.4 interrupt enabled

    __bis_SR_register(GIE);     // global interrupt enable
    while(1);
  }

  // Port 1 interrupt service routine
  #if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
  #pragma vector=PORT1_VECTOR
  __interrupt void Port_1(void)
  #elif defined(__GNUC__)
  void __attribute__ ((interrupt(PORT1_VECTOR))) Port_1 (void)
  #else
  #error Compiler not supported!
  #endif
  {
      P1OUT ^= BIT0;
      P1IFG &= ~BIT1;                         // Clear P1.4 IFG
  }
}
