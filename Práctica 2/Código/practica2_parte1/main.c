#include "44b.h"
#include "led.h"
#include "boton.h"

extern char screen[];
char *Screen = (char*) screen;

extern void DoSWI  (void);
extern void DoUndef(void);
extern void DoDabort(void);

void ISR_SWI(void) __attribute__ ((interrupt ("SWI")));
void ISR_Undef(void) __attribute__ ((interrupt ("UNDEF")));
void ISR_FIQ(void) __attribute__ ((interrupt ("FIQ")));
void ISR_Pabort(void) __attribute__ ((interrupt ("ABORT")));
void ISR_Dabort(void) __attribute__ ((interrupt ("ABORT")));
//void ISR_IRQ(void) __attribute__ ((interrupt ("IRQ")));

 

void write(char* text, char* address)
{
	while( *text != 0 ){
		*address++ = *text++;
	}
}


void ISR_Undef(void)
{
    write("Undef \0",Screen);
}


void ISR_FIQ(void)
{
    write("FIQ   \0",Screen);
}

void ISR_SWI(void)
{
    write("SWI   \0",Screen);
}

void ISR_Pabort(void)
{
    write("Pabort\0",Screen);
}

void ISR_Dabort(void)
{
    write("Dabort\0",Screen);
}

/* Configuara Puerto G (botones) y puerto B (leds) */
void InitPorts(void)
{
	/* Configura bits 9 y 10 de PCONB como salida */
	 rPCONB = 0x1cf;

    /* Configuracion del puerto G */
    rPCONG  = 0xffff;        		// Establece la funcion de los pines (EINT0-7)
	rPUPG   = 0x0;                  // Habilita el "pull up" del puerto
	//rEXTINT = rEXTINT|0x22222222;   // Configura las lineas de int. como de flanco de bajada
	rEXTINT=0x22222222;





}

void IntInit(void){

	 /*	I_ISPC: Registro de 26 bits.
		    	Si escribimos un "1" decimos que todas las interrupciones pendientes
		    	han sido atendidas. Escribir en este resgistro escribe en INTPND.	*/
		    	rI_ISPC=0xFFFFFFFF	;/* Limpiamos todas las interrupciones pendientes */
		    	rEXTINTPND = 0xf;       // Borra EXTINTPND escribiendo 1s en el propio registro

	/*	Manejo del controlador de interrupciones, hay que configurar los siguiente parámetros:
	INTCON: 3 bits: Modo Vectorizado, Habilita IRQ, Habilita FIQ (Activas a baja)
	Activamos sólo la IRQ y en modo NO vectorizado */
	rINTCON  =0x5;

	/*	INTMOD: Registro con un bit por línea. Si ponemos a 0 sus valores decimos que
	estamos usando IRQ, si ponemos 1 decimos que estamos usando FIQ para esa línea.
	Ponemos   a 0. */
	rINTMOD=0x0;			/* Inicializamos las interrupciones */

	/*	INTMSK(26): Máscara de interrupciones del controlador, activamos las líneas:
		    	EINT4/5/6/7 poniendo su bit a 0.	*/
	rINTMSK = ~(BIT_GLOBAL|BIT_EINT4567); // Emascara todas las lineas excepto eint4567 y el bit global

	InitPorts();


	  /* Por precaucion, se vuelven a borrar los bits de INTPND y EXTINTPND */
	      rI_ISPC    |= (BIT_EINT4567);
	    	rEXTINTPND = 0xf;
}





int main(void){
		IntInit();
		init_leds();
	     DoUndef();
	     DoSWI();
	     DoDabort();

	while(1);
	return (0);
}
