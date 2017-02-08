/*********************************************************************************************
* Fichero:	button.c
* Autor:		
* Descrip:	Funciones de manejo de los pulsadores (EINT6-7)
* Version:	
*********************************************************************************************/

/*--- ficheros de cabecera ---*/
#include "44b.h"
#include "def.h"
#include "led.h"
/*--- variables globales ---*/
unsigned int update = 0;

// Rutina para hacer una espera activa
void EliminaRebotes(void) {
	int i,j,k;
	i=200000;
	j=0;
	while (j!=i){
		k=k*j;
		j+=1;
	}
}
void DoDetecta(void) {
	   int which_int;
		/*TAREA 3*/
		/* Identificar la interrupcion y almacenarlo en which_int*/

		/*fin TAREA 3*/
	   which_int = rEXTINTPND;
		/* Encender/apagar el LED adecuado */
	      switch (which_int) {
	      EliminaRebotes();
	     	case 4:
	     		switchLed1();
	        	break;
	     	case 8:
	     		switchLed2();
	     	 	break;
	     	default:
	        	break;
	      }

	   /* Finalizar ISR */
	   rEXTINTPND = 0xf;				// borra los bits en EXTINTPND
	   rI_ISPC   |= BIT_EINT4567;		// borra el bit pendiente en INTPND
}



