# woody_woodpacker

> “Packers” are tools whose task consists of compressing executable programs (.exe, .dll,
> .ocx ...) and encrypting them simultaneously. During execution, a program passing
> through a packer is loaded in memory, compressed and encrypted, then it will be decom-
> pressed (decrypted as well) and finally be executed.
> The existence of such programs is related to the fact that antivirus programs gener-
> ally analyse programs when they are loaded in memory, before they are executed. Thus,
> encryption and compression of a packer allow to bypass this behavior by obfuscating the
> content of an executable until it execution.

## Objectifs:

Code a program that at first encrypt a program given as parameter (ELF-64 only).
A new program called `woody` will be generated from this execution.
When this new program `woody` will be executed, it will have to be decrypted to be run.
Its execution has to be totally identical to the original program in the last step.

## General Instructions:

* This project should be coded in C/ASM.
* A Makefile should be made.
* Allowed functions are:
	* open, close, exit
	* fputs, fflush, lseek
	* mmap, munmap
	* perror, strerror
	* syscall
	* printf family
	* libft and all the functions within it
* The executable should be named woody_woodpacker.
* An optimised encryption algorithm should be chosen.
* When running the encrypted program, it will have to display the string “....WOODY....”, followed by a newline, to indicate that the binary is encrypted. Its execution after decryption must not be altered.
* Obviously, in no way the encrypted program is allowed to crash.
* The program must not change the execution of the final binary produced.

## Example:
```c
# nl sample.c
1 #include <stdio.h>
2 int
3 main(void) {
4 printf("Hello, World!\n");
5 return (0x0);
6 }
#clang -m32 -o sample sample.c
# ./woody_woodpacker sample
File architecture not suported. x86_64 only
# clang -m64 -o sample sample.c
# ls
sample sample.c woody_woodpacker
# ./woody_woodpacker sample
key_value: 07A51FF040D45D5CD
# ls
sample sample.c woody woody_woodpacker
# objdump -D sample | tail -f -n 20
45: 67 73 2f addr16 jae 77 <_init-0x80481f9>
48: 52 push %edx
49: 45 inc %ebp
4a: 4c dec %esp
4b: 45 inc %ebp
4c: 41 inc %ecx
4d: 53 push %ebx
4e: 45 inc %ebp
4f: 5f pop %edi
50: 33 36 xor (%esi),%esi
52: 32 2f xor (%edi),%ch
54: 66 69 6e 61 6c 29 imul $0x296c,0x61(%esi),%bp
5a: 20 28 and %ch,(%eax)
5c: 62 61 73 bound %esp,0x73(%ecx)
5f: 65 64 20 6f 6e gs and %ch,%fs:0x6e(%edi)
64: 20 4c 4c 56 and %cl,0x56(%esp,%ecx,2)
68: 4d dec %ebp
69: 20 33 and %dh,(%ebx)
6b: 2e 36 2e 32 29 cs ss xor %cs:(%ecx),%ch
...
# objdump -D woody | tail -f -n 20
197: 64 69 6e 5f 75 73 65 imul $0x64657375,%fs:0x5f(%rsi),%ebp
19e: 64
19f: 00 5f 5f add %bl,0x5f(%rdi)
1a2: 6c insb (%dx),%es:(%rdi)
1a3: 69 62 63 5f 63 73 75 imul $0x7573635f,0x63(%rdx),%esp
1aa: 5f pop %rdi
1ab: 69 6e 69 74 00 5f 5f imul $0x5f5f0074,0x69(%rsi),%ebp
1b2: 62 73 (bad) {%k7}
1b4: 73 5f jae 215 <(null)-0x400163>
1b6: 73 74 jae 22c <(null)-0x40014c>
1b8: 61 (bad)
1b9: 72 74 jb 22f <(null)-0x400149>
1bb: 00 6d 61 add %ch,0x61(%rbp)
1be: 69 6e 00 5f 5f 54 4d imul $0x4d545f5f,0x0(%rsi),%ebp
1c5: 43 5f rex.XB pop %r15
1c7: 45 rex.RB
1c8: 4e rex.WRX
1c9: 44 5f rex.R pop %rdi
1cb: 5f pop %rdi
...
# ./sample
Hello, World!
# ./woody
....WOODY.....
Hello, World!
#

```


