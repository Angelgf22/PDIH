pila segment stack 'stack'
dw 100h dup (?)
pila ends
datos segment 'data'
	msg db 'Hola Mundo $'
datos ends
codigo segment 'code'
	assume cs:codigo, ds:datos, ss:pila
	main PROC
		mov ax,datos
		mov ds,ax
		mov cx,1
    ; inicializamos contador

		bucle:
			mov dx,OFFSET msg
			mov ah,9
			int 21h
			;incrementamos contador
			inc cx
			cmp cx,7
      ; comparamos el contador con 7 (7 veces)
			jne bucle
      ; repetimos (not equal)

		mov ah,9
		int 21h
		mov ax,4C00h ; terminar y salir al S.O.
		int 21h
	main ENDP
codigo ends

END main
