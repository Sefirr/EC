/*******************************************************************************************
* File:		keyboard.c
* Desc:		Funciones de teclado
* History:	
*********************************************************************************************/

/*--- Ficheros de cabecera ---*/
#include "44b.h"
#include "44blib.h"
#include "def.h"
#include "keyboard.h"
#include <stdio.h>
#include <stdlib.h>


/*--- Variables globales ---*/
volatile UCHAR *keyboard_base = (UCHAR *)0x06000000;

tCola buff;

char key;

/*--- Codigo de las funciones ---*/
void init_keyboard()
{
	rI_ISPC = 0xFFFFFFFF;

	rINTMSK &= ~(BIT_GLOBAL|BIT_EINT1);

	pISR_EINT1 = (unsigned) key_ISR;

	rPCONG = 0xFFFF;
	rPUPG = 0x0;
	rEXTINT = rEXTINT|0x22222222;   // Configura las lineas de int. como de flanco de bajada

	rI_ISPC = 0xFFFFFFFF;
}

void key_ISR(void)
{
	Delay(200);
	key = key_read();

	Delay(100);

	if (key < 0xF)
		inserta(&buff, key);

	/*FIN ISR*/
	rI_ISPC |= BIT_EINT1;
	//rI_ISPC = 0xFFFFFFFF;
}

// Funcion que devuelve un entero (0..15) que
// representa la tecla pulsada
// Debe invocarse desde la rutina de tratamiento de interrupci—n
char key_read()
{
	char value;
	char temp;
	/* leer linea 1 */
	temp = *(keyboard_base+0xfd);
	if(( temp & KEY_VALUE_MASK) != KEY_VALUE_MASK)
	{
		if( (temp&0x1) == 0 )
			value = 3;
		else if( (temp&0x2) == 0 )
			value = 2;
		else if( (temp&0x4) == 0 )
			value = 1;
		else if( (temp&0x8) == 0 )
			value = 0;
		return value;
	}
	/* linea 2 */
	temp = *(keyboard_base+0xfb);
	if(( temp & KEY_VALUE_MASK) != KEY_VALUE_MASK)
	{
		if( (temp&0x1) == 0 )
			value = 7;
		else if( (temp&0x2) == 0 )
			value = 6;
		else if( (temp&0x4) == 0 )
			value = 5;
		else if( (temp&0x8) == 0 )
			value = 4;
		return value;
	}
	/* linea 3 */
	temp = *(keyboard_base+0xf7);
	if(( temp & KEY_VALUE_MASK) != KEY_VALUE_MASK)
	{
		if( (temp&0x1) == 0 )
			value = 0xb;
		else if( (temp&0x2) == 0 )
			value = 0xa;
		else if( (temp&0x4) == 0 )
			value = 9;
		else if( (temp&0x8) == 0 )
			value = 8;
		return value;
	}
	/* linea 4 */
	temp = *(keyboard_base+0xef);
	if(( temp & KEY_VALUE_MASK) != KEY_VALUE_MASK)
	{
		if( (temp&0x1) == 0 )
			value = 0xf;
		else if( (temp&0x2) == 0 )
			value = 0xe;
		else if( (temp&0x4) == 0 )
			value = 0xd;
		else if( (temp&0x8) == 0 )
			value = 0xc;
		return value;
	}
	return -1;
}


