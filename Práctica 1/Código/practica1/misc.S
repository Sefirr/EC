.global rgb2gray
.global contarUnos
.global verdadero


.text

contarUnos:
		push {r5 - r8}

		mov r5, #0
fori:	cmp r5, r2
		bge fini

		mov r8, #0
		mov r6, #0
forj:	cmp r6, r3
		bge finj
			mul r7, r5, r3
			add r7, r7, r6
			ldrb r7, [r0, r7]
			add r8, r8, r7

			add r6, r6, #1
			b forj
finj:	lsl r7, r5, #1
		strh r8, [r1, r7]
		add r5, r5, #1
		b fori

fini:	pop {r5 - r8}
		bx lr	

rgb2gray:
		PUSH {R4-R10, FP, LR}
		ADD FP, SP, #32
		MOV R4, #0
		LDRB R5, [R0]
		LDR R6, =0X084E
		MUL R7, R5, R6
		ADD R4, R4, R7
		LDRB R5, [R0, #1]
		LDR R6, =0X01BF0
		MUL R7, R5, R6
		ADD R4, R4, R7
		LDRB R5, [R0, #2]
		LDR R6, =0X02D2
		MUL R7, R5, R6
		ADD R4, R4, R7
		MOV R0, R4
		BL div10000
		SUB SP, FP, #32
		POP {R4-R10, FP, LR}
		bx lr

div10000:
		push {fp}
		LDR     R1, =0xD1B71758
		UMULL   R3, R2, R0, R1
		MOV     R0, R2,LSR#13
 		pop {fp}
 		bx lr

verdadero:
		push {R4-R6, FP}
		ADD FP, SP, #12
		LDRB R4, [R0]
		LDRB R5, [R0, #-1]
		LDRB R6, [R0, #-4]
		cmp R4, #1
		BNE fin
		CMP R4, R5
		BNE pintar
		CMP R4, R6
		BNE pintar
		MOV R0, #0

fin:
		SUB SP, FP, #12
		pop {R4-R6, FP}
		bx lr
pintar:
		MOV R0, #1
		b fin

