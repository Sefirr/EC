.global start

.global _ISR_STARTADDRESS

.global DoUndef
.global DoSWI
.global DoDabort

.global screen

.extern main
.extern ISR_Undef
.extern ISR_SWI
.extern ISR_FIQ
.extern ISR_Pabort
.extern ISR_Dabort

.extern DoDetecta

.equ 	_ISR_STARTADDRESS,	0xc7fff00		/* GCS6:64M DRAM/SDRAM 	*/
.equ    UserStack,   _ISR_STARTADDRESS-0xf00         /* c7ff000 */
.equ    SVCStack,    _ISR_STARTADDRESS-0xf00+256     /* c7ff100 */
.equ    UndefStack,  _ISR_STARTADDRESS-0xf00+256*2   /* c7ff200 */
.equ    AbortStack,  _ISR_STARTADDRESS-0xf00+256*3   /* c7ff300 */
.equ    IRQStack,    _ISR_STARTADDRESS-0xf00+256*4   /* c7ff400 */
.equ    FIQStack,    _ISR_STARTADDRESS-0xf00+256*5   /* c7ff500 */

.equ    HandleReset,    _ISR_STARTADDRESS
.equ    HandleUndef,    _ISR_STARTADDRESS+4
.equ    HandleSWI,      _ISR_STARTADDRESS+4*2
.equ    HandlePabort,   _ISR_STARTADDRESS+4*3
.equ    HandleDabort,   _ISR_STARTADDRESS+4*4
.equ    HandleReserved, _ISR_STARTADDRESS+4*5
.equ    HandleIRQ,      _ISR_STARTADDRESS+4*6
.equ    HandleFIQ,      _ISR_STARTADDRESS+4*7

/* Simbolos para facilitar la codificación
de los modos de ejecución */
.equ 	USERMODE,	0x10
.equ 	FIQMODE,	0x11
.equ 	IRQMODE,	0x12
.equ 	SVCMODE,	0x13
.equ 	ABORTMODE,	0x17
.equ 	UNDEFMODE,	0x1b
.equ 	MODEMASK,	0x1f

.equ 	NOINT,		0xc0   /* Máscara para deshabilitar interrupciones */
.equ    IRQ_MODE,	0x40   /* deshabilitar interrupciones en modo IRQ  */
.equ    FIQ_MODE,	0x80   /* deshabilitar interrupciones en modo FIQ  */

.equ I_ISPR, 0x1e00020
.equ EXTINTPND, 0x1d20054

.text
start:
    /* Si comenzamos con un reset
     el procesador esta en modo supervisor */
    bic	    r0,r0,#MODEMASK
    orr	    r1,r0,#SVCMODE
    msr	    cpsr_cxsf,r1 	    /* SVCMode */
    /* Si comenzamos con un reset el procesador esta en modo supervisor */
    /* Si comenzamos con un reset
     el procesador esta en modo supervisor.
     Tras InitStacks DEBEMOS seguir en modo supervisor*/
    bl InitStacks
	
    /* Seguimos en modo supervisor, configuramos
       las direcciones de las rutinas de tratamiento
       de excepciones */
    bl InitISR

    /* Pasamos a MODO USUARIO, inicializamos su pila
      y ponemos a cero el frame pointer*/
    mrs	    r0,cpsr
   	bic	r0,r0,#MODEMASK
    orr	r1,r0,#USERMODE
	BICNE   R0, R0, #0x80     // Habilita IRQ,
    msr	cpsr_cxsf,r1 	    /* SVCMode */
    ldr sp,=UserStack
    mov fp,#0

    /* Saltamos a Main */
    bl main
	b .
InitStacks:
    /* Código de la primera parte */
	/*TAREA 1a*/
	/*El alumno/a debe realizar la inicializacion de los punteros de pila (registros SP) de los modos 
	UndefMode,  AbortMode , IRQMode , FIQMode  y  SVCMode */
	/* Inicialización de la pila del modo UndefMode */
	mrs r0, cpsr
	bic r0, r0, #MODEMASK
	orr r1, r0, #UNDEFMODE
	msr cpsr_cxsf, r1
	ldr sp, =UndefStack
	/* Inicialización de la pila del modo AbortMode */
	mrs r0, cpsr
	bic r0, r0, #MODEMASK
	orr r1, r0, #ABORTMODE
	msr cpsr_cxsf, r1
	ldr sp, =AbortStack
	/* Inicialización de la pila del modo IRQMode */
	mrs r0, cpsr
	bic r0, r0, #MODEMASK
	orr r1, r0, #IRQMODE
	msr cpsr_cxsf, r1
	ldr sp, =IRQStack
	/* Inicialización de la pila del modo FIQMode */
	mrs r0, cpsr
	bic r0, r0, #MODEMASK
	orr r1, r0, #FIQMODE
	msr cpsr_cxsf, r1
	ldr sp, =FIQStack
	/* Inicialización de la pila del modo SVCMode */
	mrs r0, cpsr
	bic r0, r0, #MODEMASK
	orr r1, r0, #SVCMODE
	msr cpsr_cxsf, r1
	ldr sp, =SVCStack
	/*Fin TAREA 1a*/
    mov pc, lr


//  Debemos comprobar la fuente de la interrupcion.
// Para ello habra que mirar en (INTOND o I_ISPR)??? y EXTINTPND
ISR_IRQ:
	/*TAREA 2 definir la rutina ISR_IRQ*/
	/*El alumno/a debe implementar esta rutina, que comprobara si se ha pulsado un boton, y si saltará en caso afirmativo a la funcion DoDetecta*/
	/*Ayuda: No olvideis que esta rutina debe cargar en PC la direccion de retorno al terminar*/
	/*Ayuda: Los registros I_ISPR y EXTINTPND nos proporcionan informacion de las interrupciones pendientes de atender*/
	push {r0-r10, fp}
	add fp, sp, #44
	ldr r0, =I_ISPR
	ldr r1, =EXTINTPND
	ldr r0, [r0]
	cmp r0, #0x0
	beq fin
led1:
	cmp r1, #0x4 //Botón izquierdo
	beq detectado
led2:
	cmp r1, #0x8 //Botón derecho
	beq detectado
	bne fin
detectado:
	bl DoDetecta
fin:
	sub sp, fp, #44
	pop {r0-r10, fp}
	subs pc, lr, #4

	/*Fin TAREA 2*/


InitISR:
    /* Código de la primera parte */
	/*TAREA 1b*/
	/*El alumno/a debe definir la tabla de direcciones de rutinas*/
	/*Ayuda: las entradas de la tabla son HandleUndef,HandleDabort, HandlePabort, HandleIRQ, HandleSWI, y HandleFIQ*/
	// Tabla de direcciones de ISRs
	//Direccion de la rutina de tratamiento de la excepción Undef
	ldr r0, =ISR_Undef
	ldr r1, =HandleUndef
	str r0, [r1]
	//Direccion de la rutina de tratamiento de la excepción Dabort
	ldr r0, =ISR_Dabort
	ldr r1, =HandleDabort
	str r0, [r1]
	//Direccion de la rutina de tratamiento de la excepción Pabort
	ldr r0, =ISR_Pabort
	ldr r1, =HandlePabort
	str r0, [r1]
	//Direccion de la rutina tratamiento de la excepción SWI
	ldr r0, =ISR_SWI
	ldr r1, =HandleSWI
	str r0, [r1]
	//Direccion de la rutina tratamiento de la excepción SWI
	ldr r0, =ISR_FIQ
	ldr r1, =HandleFIQ
	str r0, [r1]
	//Direccion de la rutina tratamiento de la excepción SWI
	ldr r0, =ISR_IRQ
	ldr r1, =HandleIRQ
	str r0, [r1]
	/*fin TAREA 1b*/
	mov pc,lr


DoSWI:
	swi #0
	mov pc,lr

DoUndef:
	.word 0xE6000010
	mov pc,lr

DoDabort:
	ldr r0,=0x0a333333
	str r0,[r0]
	mov pc,lr


screen:
	.space 1024

.end
