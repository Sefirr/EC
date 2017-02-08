/*********************************************************************************************
* Fichero:		timer.c
* Autor:		
* Descrip:		funciones de control del timer0 del s3c44b0x
* Version:	
*********************************************************************************************/

/*--- ficheros de cabecera ---*/
#include "44b.h"
#include "44blib.h"

/*--- variables globales ---*/
extern int symbol;
extern int pausa;
extern int resetsymbol;

/*--- funciones externas ---*/
extern void leds_switch();
extern void D8Led_symbol(int value);

//*--- declaracion de funciones ---*/
void timer_ISR(void) __attribute__ ((interrupt ("IRQ")));
void timer_init(void);

/*--- codigo de las funciones ---*/
void timer_ISR(void)
{  /*  TAREA 2a */
        /*Actualizar leds con cada int. del timer */
		if (resetsymbol == 1){
				symbol = 0x09;	 /* actualizamos el contador a 9 */
				resetsymbol=0;
				pausa = 1;
		} else if (pausa == 0) {
			if(symbol > 0)
				symbol--;	 /* actualiza el contador segun proceda */
		}
		D8Led_symbol(symbol); 		     /* muestra el contador en el display */
		leds_switch(); 

		/* Finalizar ISR */
		    rEXTINTPND = 0xf;		// borra los bits en EXTINTPND
		    rI_ISPC = BIT_TIMER0;	// borra el bit pendiente en INTPND
	/*fin Tarea 2a*/
}

void timer_init(void)
{

	/* Configura el Timer0 */
	    rTCFG0 = 63;
	    rTCFG1 = 0x0;
	    rTCNTB0 = 65535;
	    rTCMPB0 = 12800;
	    /* establecer update=manual + inverter=on */
		rTCON = 0x2;
		/* inicial timer con auto-reload */
	    rTCON  = 0x09;

/*TAREA 2b*/
	/* Establece la rutina de servicio para TIMER0 */
	    pISR_TIMER0=(unsigned)timer_ISR;

	/*Configurar controlador de interrupciones */
		rI_ISPC = 0x3ffffff; // Borra INTPND escribiendo 1s en I_ISPC.
		rEXTINTPND = 0xf; // Borra EXTINTPND escribiendo 1s en el propio registro.
		rINTMOD = 0;  // Configura las lineas como de tipo IRQ
		rINTCON |= 0x1; // Habilita int. vectorizadas y la linea IRQ (FIQ no)

	// habilita Timer0 y el bit global
		rINTMSK &= ~(BIT_TIMER0|BIT_GLOBAL);

	/* Por precaucion, se vuelven a borrar los bits de INTPND y EXTINTPND */
		rI_ISPC = BIT_TIMER0; // Borra INTPND escribiendo 1s en I_ISPC.
		rEXTINTPND = 0xf; // Borra EXTINTPND escribiendo 1s en el propio registro.

/*fin TAREA 2b*/	

}
