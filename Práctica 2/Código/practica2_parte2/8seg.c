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

/* Mapa de bits de cada segmento 
  (valor que se debe escribir en el display para que se ilumine el segmento) */
#define SEGMENT_A		~0x80		
#define SEGMENT_B		~0x40
#define SEGMENT_C		~0x20
#define SEGMENT_D		~0x08
#define SEGMENT_E		~0x04
#define SEGMENT_F		~0x02
#define SEGMENT_G		~0x01
#define SEGMENT_P		~0x10

/*--- variables globales ---*/
/* tabla de segmentos */
int Symbol[] = { SEGMENT_A, SEGMENT_B, SEGMENT_C, SEGMENT_D, SEGMENT_E, SEGMENT_G,SEGMENT_F, SEGMENT_P};
			  					  
/*--- declaración de funciones ---*/
void D8Led_init(void);
void D8Led_symbol(int value); 

/*--- código de las funciones ---*/
void D8Led_init(void)
{
    /* Estado inicial del display con todos los segmentos iluminados 
       (buscar en los ficheros de cabera la direccion implicada) */
    LED8ADDR = 0 ;
}

void D8Led_symbol(int value)
{
/*Tarea 3*/
	/* muestra el Symbol[value] en el display   */
	if(value == 0x9)
		LED8ADDR = Symbol[0] & Symbol[1] & Symbol[2] & Symbol[3] & Symbol[5] & Symbol[6];
	else if(value == 0x8)
		LED8ADDR = Symbol[0] & Symbol[1] & Symbol[2] & Symbol[3] & Symbol[4] & Symbol[5] & Symbol[6];
	else if(value == 0x7)
			LED8ADDR = Symbol[0] & Symbol[1] & Symbol[2];
	else if(value == 0x6)
			LED8ADDR = Symbol[0] &  Symbol[2] & Symbol[3] &  Symbol[4] & Symbol[5] &  Symbol[6];
	else if(value == 0x5)
			LED8ADDR = Symbol[0] & Symbol[2] & Symbol[3] & Symbol[5] & Symbol[6];
	else if(value == 0x4)
			LED8ADDR = Symbol[1] & Symbol[2] & Symbol[5] & Symbol[6];
	else if(value == 0x3)
			LED8ADDR = Symbol[0] & Symbol[1] & Symbol[2] & Symbol[3] & Symbol[6];
	else if(value == 0x2)
			LED8ADDR = Symbol[0] & Symbol[1] & Symbol[3] & Symbol[4] & Symbol[6];
	else if(value == 0x1)
			LED8ADDR = Symbol[1] & Symbol[2];
	else if(value == 0x0)
			LED8ADDR = Symbol[0] & Symbol[1] & Symbol[2] & Symbol[3] & Symbol[4] & Symbol[5];
		
/*fin Tarea 3*/		
}
