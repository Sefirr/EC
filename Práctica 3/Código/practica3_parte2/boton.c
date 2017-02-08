/*
 * boton.c
 *
 *  Created on: 14/05/2014
 *      Author: usuario_local
 */

#include "boton.h"

extern int modo;
extern int frecuencia;


/*--- codigo de funciones ---*/
void Eint4567_init(void)
{
/*TAREA 1a*/
	/* Configuracion del controlador de interrupciones */
	rI_ISPC = 0xFFFFFFFF;					// Borra INTPND
	rEXTINTPND = 0xF;						// Borra EXTINTPND
	rINTMOD = 0;							// Configura las linas como de tipo IRQ mediante rINTMOD
	rINTCON = 0b0001;	 					// Habilita int. vectorizadas y la linea IRQ (FIQ no) mediante rINTCON
	rINTMSK &= ~(BIT_GLOBAL|BIT_EINT4567);	// Emascara todas las lineas excepto eint4567 y el bit global mediante rINTMSK

	/* Establece la rutina de servicio para Eint4567 */
    pISR_EINT4567 = (int)Eint4567_ISR;

    /* Configuracion del puerto G */
    rPCONG  = 0xffff;        		// Establece la funcion de los pines (EINT0-7)
	rPUPG   = 0x0;                  // Habilita el "pull up" del puerto
	rEXTINT = rEXTINT|0x22222222;   // Configura las lineas de int. como de flanco de bajada

    /* Por precaucion, se vuelven a borrar los bits de INTPND y EXTINTPND */
	rI_ISPC = 0xFFFFFFFF;	// Borra INTPND
	rEXTINTPND = 0xF;		// Borra EXTINTPND
/*fin TAREA 1a*/
}
void Eint4567_ISR(void)
{
    int which_int;
	/*TAREA 1b*/
    /* Idenficiar la interrupcion */
    if(rEXTINTPND == 0x8 || rEXTINTPND == 0xc)
    	which_int = 0;
	else if(rEXTINTPND == 0x4)
		which_int = 1;

    Delay(200);

	/* Reflejar en update el sentido de la actualizacion
	   Nota: para solucionar los problemas de rebotes en el pulsador
             solo se modifica update cuando se encuentra a cero */

       switch (which_int) {
      	case 0:
      		modo = MODO_PEDIR;
         	break;
      	case 1:
      		if(frecuencia == FRECUENCIA_NORMAL) {
      			frecuencia = FRECUENCIA_RAPIDA;
      			rTCFG0 = 112;
      			Uart_SendString("Frecuencia Rapida\n");
      		} else {
      			frecuencia = FRECUENCIA_NORMAL;
      			rTCFG0 = 255;
      			Uart_SendString("Frecuencia Normal\n");
      		}
      		break;
      	default:
         	break;
       }

    /* Finalizar ISR */
    rEXTINTPND = 0xF;			// borra los bits en EXTINTPND
    rI_ISPC  |= (BIT_EINT4567); // borra el bit pendiente en INTPND
	/*fin TAREA 1b*/
}

