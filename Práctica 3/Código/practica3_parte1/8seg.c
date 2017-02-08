/*********************************************************************************************
* Fichero:	8led.c
* Autor:		
* Descrip:	Funciones de control del display 8-segmentos
* Version:	
*********************************************************************************************/

/*--- ficheros de cabecera ---*/
#include "44b.h"
#include "def.h"


/*--- definicion de macros ---*/
#define	LED8ADDR	(*(volatile unsigned char *)(0x2140000))

/* Mapa de bits de cada segmento    */
#define SEGMENT_A		0x80		
#define SEGMENT_B		0x40
#define SEGMENT_C		0x20
#define SEGMENT_D		0x08
#define SEGMENT_E		0x04
#define SEGMENT_F		0x02
#define SEGMENT_G		0x01
#define SEGMENT_P		0x10

/*--- Mapa de bits de los digitos decimales ---*/
#define DIGIT_0 SEGMENT_F | SEGMENT_P
#define DIGIT_1 SEGMENT_A | SEGMENT_D | SEGMENT_E | SEGMENT_F | SEGMENT_G | SEGMENT_P
#define DIGIT_2 SEGMENT_C | SEGMENT_G | SEGMENT_P
#define DIGIT_3 SEGMENT_E | SEGMENT_G | SEGMENT_P
#define DIGIT_4 SEGMENT_A | SEGMENT_D | SEGMENT_E | SEGMENT_P
#define DIGIT_5 SEGMENT_B | SEGMENT_E | SEGMENT_P
#define DIGIT_6 SEGMENT_B | SEGMENT_P
#define DIGIT_7 SEGMENT_D | SEGMENT_E | SEGMENT_F | SEGMENT_G | SEGMENT_P
#define DIGIT_8 SEGMENT_P
#define DIGIT_9 SEGMENT_D | SEGMENT_E | SEGMENT_P
#define DIGIT_A SEGMENT_D | SEGMENT_P
#define DIGIT_B SEGMENT_A | SEGMENT_B | SEGMENT_P
#define DIGIT_C SEGMENT_B | SEGMENT_C | SEGMENT_F | SEGMENT_P
#define DIGIT_D SEGMENT_A | SEGMENT_G | SEGMENT_P
#define DIGIT_E SEGMENT_B | SEGMENT_C | SEGMENT_P
#define DIGIT_F SEGMENT_B | SEGMENT_C | SEGMENT_D | SEGMENT_P


/*--- variables globales ---*/

/* tabla de simbolos */
int Symbol[] = {DIGIT_0, DIGIT_1, DIGIT_2, DIGIT_3, DIGIT_4, DIGIT_5, DIGIT_6, DIGIT_7, DIGIT_8, DIGIT_9, DIGIT_A, DIGIT_B, DIGIT_C, DIGIT_D, DIGIT_E, DIGIT_F, };

			  					  
/*--- declaración de funciones ---*/
void D8Led_init(void);
void D8Led_symbol(int value); 

/*--- código de las funciones ---*/
void D8Led_init(void)
{
    /* Estado inicial del display con todos los segmentos iluminados 
       (buscar en los ficheros de cabera la direccion implicada) */
    LED8ADDR = 0x0;
}

void D8Led_symbol(int value)
{
	/* muestra el Symbol[value] en el display (analogo al caso anterior) */
	if( (value >= 0) && (value < 16) )
		LED8ADDR = Symbol[value];
}
