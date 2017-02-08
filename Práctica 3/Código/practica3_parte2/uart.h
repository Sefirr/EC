/*********************************************************************************************
* Fichero:	uart.h
* Autor:	
* Descrip:	cabecera de las funciones de UART
* Version:
*********************************************************************************************/

#ifndef __UART_H__
#define __UART_H__

#ifdef __cplusplus
extern "C" {
#endif

/*--- definicón de constantes ---*/
#define LF_char 0x0A	/* Caracter de salto de línea */
#define CR_char 0x0D    /* Caracter de retorno de carro */

/*--- prototipos de funciones 
  (NO ES OBLIGAOTRIO MANTENERLOS )---*/
void Uart_Init(int baud);
char Uart_Getch(void);
void Uart_SendByte(int data);
void Uart_SendString(char *pt);
void Uart_Printf(char *fmt,...);

#ifdef __cplusplus
}
#endif

#endif /* __UART_H__ */
