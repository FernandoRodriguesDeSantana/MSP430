#include <msp430.h>

// CONFIGURANDO ENTRADAS E SAÍDAS
void main(void)
{
    WDTCTL = WDTPW | WDTHOLD;    // Para o watchdog timer

    // CONFIGURANDO O LED EM P1.0
    P1DIR |= BIT0;              // Configurando P1.0 como saída
    P1OUT &= ~BIT0;             // LED inicia apagado

    // CONFIGURANDO O LED EM P4.7
    P4DIR |= BIT7;              // Configurando P4.7 como saída
    P4OUT &= ~BIT7;             // LED inicia apagado

    // CONFIGURANDO O BOTÃO EM P1.1
    P1DIR &= ~BIT1;             // Configurando P1.1 como entrada
    P1REN |= BIT1;              // Habilitando resistor em P1.1
    P1OUT |= BIT1;              // Definindo resistor em P1.1 como PULL-UP
    P1IES |= BIT1;              // Interrupção na borda de descida
    P1IFG &= ~BIT1;             // Limpa a flag de interrupção
    P1IE |= BIT1;               // Habilita interrupção em P1.1

    __bis_SR_register(GIE);     // Habilita interrupções globais

    while (1)
    {
        __no_operation();       // Apenas para depuração
    }
}

// CONFIGURANDO INTERRUPÇÕES
#pragma vector = PORT1_VECTOR;
__interrupt void Port_1(void)
{
    static unsigned char state = 0;     // Variável de estado para alternância
    state ^= 1;                         // Alterna estado

    if(state){
        P1OUT |= BIT0;                  // Liga LED em P1.0
        P4OUT &= ~BIT7;                 // Desliga LED em P4.7
    } else{
        P1OUT &= ~BIT0;                 // Apaga LED em P1.0
        P4OUT |= BIT7;                  // Acende LED em P4.7
    }

    _delay_cycles(100000);              // Deboucing simples
    P1IFG &= ~BIT1;                     // Limpa a flag de interrupção

}

