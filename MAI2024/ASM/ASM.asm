.586
.model flat, stdcall
includelib D:\Visual_Lab_3sem\Course_Project_MAI_2024\MAI2024\Debug\StandartLib.lib
includelib kernel32.lib
includelib libucrt.lib

ExitProcess PROTO : DWORD
copystr PROTO : DWORD, : DWORD
joinst PROTO : DWORD, : DWORD
outstr PROTO : DWORD
outint PROTO : SDWORD 
.stack 4096
.const
	overflow db 'ERROR: VARIABLE OVERFLOW', 0 
	null_division db 'ERROR: DIVISION BY ZERO', 0
	L1 SDWORD 5
	L3 SDWORD 0
.data
	chiefa SDWORD 0
.code

main PROC
	push L1
	push L1
	pop eax
	pop ebx
	add eax, ebx
	jo EXIT_OVERFLOW
	push eax
	pop chiefa
	push L3
	push 0
	call ExitProcess


	jmp EXIT
	EXIT_DIV_ON_NULL:
	push offset null_division
	call outstr
	push - 1
	call ExitProcess

	EXIT_OVERFLOW:
	push offset overflow
	call outstr
	push - 2
	call ExitProcess

	EXIT:
	push 0
	call ExitProcess

main ENDP
end main