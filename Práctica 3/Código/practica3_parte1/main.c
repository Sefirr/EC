    /*********************************************************************************************
* Fichero:	main.c
* Autor:	
* Descrip:	punto de entrada de C
* Version:	<P4-ARM.8seg-button>
*********************************************************************************************/

/*--- ficheros de cabecera ---*/
#include "44blib.h"
#include "44b.h"
#include "keyboard.h"
#include "timer.h"
#include "game.h"

/*--- variables globales ---*/
int symbol = 12;

/*--- funciones externas ---*/
extern void D8Led_symbol(int value);
/*--- codigo de las funciones ---*/
int main(void)
{	
    sys_init();			/* Inicializacion de la placa, interrupciones, puertos y UART */

    init_keyboard();
    init_timer();

	D8Led_symbol(symbol);	/* muestra el simbolo inicial en el display */
		
    game();

    return 0;
}
