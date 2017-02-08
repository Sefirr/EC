/*********************************************************************************************
* Fichero:	main.c
* Descrip:	punto de entrada de C
* Version:	<P4-ARM.8seg-button>
*********************************************************************************************/

#define BAUD_RATE 57600

// #define UART_DEBUG

#include "44blib.h"
#include "44b.h"
#include "keyboard.h"
#include "timer.h"
#include "uart.h"
#include "game.h"
#include "boton.h"

void init_intr() {
	rINTMOD = 0x0;		// Configura las linas como de tipo IRQ mediante rINTMOD
	rINTCON = 0b0001;	// Modo vectorizado e IRQ sin FIQ

    init_keyboard();
    init_timer();
    Eint4567_init();
}

int main(void)
{	
    sys_init();			/* Inicializacion de la placa, interrupciones, puertos y UART */
    Uart_Init(BAUD_RATE);
	#ifdef UART_DEBUG
    	while(1) {
    		char c = Uart_Getch();
    		Uart_SendByte(c);
    	}
	#else
    	init_intr();
    	game();
	#endif
    return 0;
}
