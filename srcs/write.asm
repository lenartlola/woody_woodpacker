section .text
bits 64
default rel
global _start

;;; lenart
;;; nasm -f bin write.asm -o bin
;;; Get the formated shellcode as following
;;; hexdump -v -e '"\\\x\" 1/1 "%02x"' bin


_start:
	xor eax, eax
	mov rdi, 0		; 0 to rdi which is the file descriptor where we want to write
	lea rsi, [rel message]	; load the effective address of the message, we could also use mov, to buffer
	mov rdx, 14		; the count of bytes we want to write
	mov eax, 1		; the write systemcall according to linux syscalls table
	syscall			; trigger the syscall

	;; We want to encrypt the text section and then call the original entry
	lea rax, [o_entry]
	add rax, qword [o_entry]
	sub rax, qword [new_entry]
	sub rax, o_entry
	push rax
	lea rdi, [code]
	add rdi, qword [code]
	sub rdi, qword [new_entry]
	sub rdi, code
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

;;; These variables are here just to allocate memory,
;;; they will be replaced with those in the t_patch struct.
o_entry dq 0
code dq 0
code_size dq 0
key dq 0
new_entry dq 0
