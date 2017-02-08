/*********************************************************************************************
* Fichero:		led.c
* Autor:		
* Descrip:		funciones de control de los LED de la placa
* Version:	
*********************************************************************************************/

/*--- ficheros de cabecera ---*/
#include "44b.h"
#include "44blib.h"

/*--- variables globales ---*/
// estado del LED: 0 -> ambos apagados. 1 -> Led1 encendido
// 2 -> led2 encendido. 3 -> ambos encendidos
int led_state;

/*--- declaracion de funciones ---*/
void leds_on();							// todos los leds encendidos 
void leds_off();						// todos los leds apagados 
void led1_on();							// led 1 encendido 	
void led1_off();						// led 1 apagado 	
void led2_on();							// led 2 encendido 	
void led2_off();						// led 2 apagado
void switchLed1();						// Cambiar el estado del led1
void switchLed2();						// Cambiar el estado del led2
void leds_switch();						// invierte el valor de los leds 
void Led_Display(int LedStatus);		// control directo del LED 	


// Inicializamos los leds encendiendo ambos
void init_leds() {
	rPCONB = 0x1cf;
	rPDATB = 0x000;
	led_state = 0x3;
}
/*--- codigo de las funciones ---*/
void leds_on()
{
	Led_Display(0x3);
}

void leds_off()
{
	Led_Display(0x0);
}

void led1_on()
{
	led_state = led_state | 0x1;
	Led_Display(led_state);
}

void led1_off()
{
	led_state = led_state & 0xfe;
	Led_Display(led_state);
}

void led2_on()
{
	led_state = led_state | 0x2;
	Led_Display(led_state);
}

void led2_off()
{
	led_state = led_state & 0xfd;
	Led_Display(led_state);
}
void switchLed1() {
/*TAREA 4a*/
/*El alumno/a debe completar esta funcion para que cambie el estado del led 1, 
si estaba encendido debera apagarlo
y si esta apagado encenderlo */
	led_state = led_state ^ 0x01;
	Led_Display(led_state);

/*fin TAREA 4a*/
}

void switchLed2() {
/*TAREA 4b*/
/*El alumno/a debe completar esta funcion para que cambie el estado del led 2, 
si estaba encendido debera apagarlo
y si esta apagado encenderlo */
	led_state = led_state ^ 0x02;
	Led_Display(led_state);
/*fin TAREA 4b*/
}

void leds_switch ()
{
    led_state ^= 0x03;
    Led_Display(led_state);
    
}

void Led_Display(int LedStatus)
{	
	led_state = LedStatus;
	
	if((LedStatus&0x01)==0x01)
		rPDATB=rPDATB&0x5ff; /* poner a 0 el bit 9 del puerto B */
	else
		rPDATB=rPDATB|0x200; /* poner a 1 el bit 9 del puerto B */
	
	if((LedStatus&0x02)==0x02)
		rPDATB=rPDATB&0x3ff; /* poner a 0 el bit 10 del puerto B */
	else
		rPDATB=rPDATB|0x400; /* poner a 1 el bit 10 del puerto B */
}
