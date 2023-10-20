section .text
bits 64

global _start

; lenart
; nasm -f bin write.asm -o bin
; Get the formated shellcode as following
; hexdump -v -e '"\\\x\" 1/1 "%02x"' bin


_start:
	xor eax, eax
	mov rdi, 0		; 0 to rdi which is the file descriptor where we want to write
	lea rsi, [rel message]	; load the effective address of the message, we could also use mov, to buffer
	mov rdx, 14		; the count of bytes we want to write
	mov eax, 1		; the write systemcall according to linux syscalls table
	syscall			; trigger the syscall

	mov eax, 60		; we want to exit in order to avoid the segmentation fault
	syscall

	;; We want to encrypt the text section and then call the original entry
	lea rax, [o_entry]
	add rax, qword [o_entry]
	sub rax, qword [new_entry]
	sub rax, o_entry
	push rax

	lea rdi, [code]
	add rdi, qword [code]
	sub rdi, qword [new_entry]
	sub rdi, new_entry
	mov rcx, qword [code_size]
	mov rax, qword [key]

decrypt:
	xor byte [rdi], al
	ror rax, 1
	add rdi, 1
	loop decrypt
	mul ecx
	ret
	
	
message db "....WOODY....",10 ; 10 is used for newline
o_entry resd 1		      ; resq 1 for 32-bit
code resd 1
code_size resd 1
key resd 1
new_entry resd 1
