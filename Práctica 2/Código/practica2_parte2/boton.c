/*********************************************************************************************
* Fichero:	button.c
* Autor:		
* Descrip:	Funciones de manejo de los pulsadores (EINT6-7)
* Version:	
*********************************************************************************************/

/*--- ficheros de cabecera ---*/
#include "44b.h"
#include "def.h"
/*--- variables globales ---*/
unsigned int update = 0;
unsigned int pausa = 0;
unsigned int resetsymbol=0;

/*--- declaracion de funciones ---*/
void Eint4567_ISR(void) __attribute__ ((interrupt ("IRQ"))); 
void Eint4567_init(void);
void EliminaRebotes(void);

#define INTPND  (*(volatile unsigned *)0x01E00004)

/*--- codigo de funciones ---*/
void Eint4567_init(void)
{
/*TAREA 1a*/
    
    /* Configuracion del puerto G */
    	rPCONG  = 0xffff;        		// Establece la funcion de los pines (EINT0-7)
		rPUPG   = 0x0;                  // Habilita el "pull up" del puerto
		rEXTINT = rEXTINT|0x22222222;   // Configura las lineas de int. como de flanco de bajada

	/* Establece la rutina de servicio para Eint4567 */
		pISR_EINT4567 = (int)Eint4567_ISR;

	/* Configurar del controlador de interrupciones */
		rI_ISPC = 0x3ffffff; // Escribimos 1s en I_ISPC para que se borren todos los bits de interrupciones pendientes del registro I_ISPC
		rEXTINTPND = 0xf;		   // Borra EXTINTPND escribiendo 1s en el propio registro.
		rINTMOD = 0; // Configura las lineas como de tipo IRQ mediante rINTMOD
		rINTCON |= 0x1; // Habilita int. vectorizadas y la linea IRQ (FIQ no) mediante rINTCON

	// Enmascara todas las lineas excepto eint4567 y el bit global mediante rINTMSK
		rINTMSK = ~(BIT_EINT4567|BIT_GLOBAL);

    /* Por precaucion, se vuelven a borrar los bits de INTPND y EXTINTPND */
		rI_ISPC = 0x3ffffff; // Borra INTPND escribiendo 1s en I_ISPC.
		rEXTINTPND = 0xf; // Borra EXTINTPND escribiendo 1s en el propio registro.
/*fin TAREA 1a*/  
}

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

void Eint4567_ISR(void)
{          
    int which_int;
	/*TAREA 1b*/
    /* Identificar la interrupción */
    	which_int = rEXTINTPND;

    /* Código para eliminar rebotes*/
    	EliminaRebotes();
	/* Reflejar en update el sentido de la actualización
	   Nota: para solucionar los problemas de rebotes en el pulsador 
             solo se modifica update cuando se encuentra a cero */ 

       switch (which_int) {
      	case 4: // Botón izquierdo
      		resetsymbol=1;
      	 	update = 5; // actualizar al simbolo anterior
      	 	break;
      	case 8: // Botón derecho
      	    pausa= ! pausa;
      	    update = 1; // actualizar al simbolo siguiente
      	    break;
      	default:
         	break;
       } 
    
    /* Finalizar ISR */    
       rEXTINTPND = 0xf;				// borra los bits en EXTINTPND
       rI_ISPC    = BIT_EINT4567;		// borra el bit pendiente en INTPND
	/*fin TAREA 1b*/	
}

