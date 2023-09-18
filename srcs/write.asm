section .text
bits 64

global _start

; lenart
; nasm -f bin write.asm -o bin
; Get the formated shellcode as following
; hexdump -v -e '"\\\x\" 1/1 "%02x"' bin


_start:
	mov rdi, 0		; 0 to rdi which is the file descriptor where we want to write
	lea rsi, [rel m]	; load the effective address of the message, we could also use mov, to buffer
	mov rdx, 14		; the count of bytes we want to write
	mov eax, 1		; the write systemcall according to linux syscalls table
	syscall			; trigger the syscall

	mov eax, 60		; we want to exit in order to avoid the segmentation fault
	syscall

m db "....WOODY....",10 ; 10 is used for newline
