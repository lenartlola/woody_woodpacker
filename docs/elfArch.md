# The anatomy of ELF

readelf is a program that recognizes and displays the ELF metadata
of a binary file, be it an object file or an executable binary. ELF, or Executable
and Linkable Format, is the content at the very beginning of an executable
to provide an operating system necessary information to load into main
memory and run the executable.

ELF can be thought of similar to the
table of contents of a book. In a book, a table of contents list the page
numbers of the main sections, subsections, sometimes even figures and
tables for easy lookup. Similarly, ELF lists various sections used for code
and data, and the memory addresses of each symbol along with other information.

An ELF binary is composed of:

* ELF header: the very first section of an executable that describes ELF header
  the file’s organization.
* Program header table: an array of fixed-size structures that describes segments of an executable.
* Section header table: an array of fixed-size structures that describes sections of an executable.
* Segments and sections: The main content of an ELF binary, which are the code and data, divided into chunks of different purpose.

A segment is a composition of zero or more sections and is directly loaded
by an operating system at runtime.

A section is a block of binary that is either:
- actual program code and data that is available in memory when a program runs.
- metadata about other sections used only in the linking process, and disappear from the final executable.    

Linker uses sections to build segments.

### ELF in detail:

From the man page:
> The header file <elf.h> defines the format of ELF executable binary files. Amongst these files are normal executable files, relocatable object files, core files, and shared objects. 

Let's analyze throw an example.

First I will write a program

```c
// hello.c
// gcc -o hello hello.c

#include <stdio.h>

int main(void)
{
	printf("Hello, World!\n");
	return 0x0;
}
```

Then ```readelf -h hello``` gives:

```shell
ELF Header:
  Magic:   7f 45 4c 46 02 01 01 00 00 00 00 00 00 00 00 00 
  Class:                             ELF64
  Data:                              2's complement, little endian
  Version:                           1 (current)
  OS/ABI:                            UNIX - System V
  ABI Version:                       0
  Type:                              DYN (Position-Independent Executable file)
  Machine:                           Advanced Micro Devices X86-64
  Version:                           0x1
  Entry point address:               0x1040
  Start of program headers:          64 (bytes into file)
  Start of section headers:          18192 (bytes into file)
  Flags:                             0x0
  Size of this header:               64 (bytes)
  Size of program headers:           56 (bytes)
  Number of program headers:         13
  Size of section headers:           64 (bytes)
  Number of section headers:         37
  Section header string table index: 36
```

* Magic: this field displays the row bytes that uniquely addresses a file is an ELF executable binary. Each byte gives brief information.
  * ```7f 45 4c 46```: are predefined values, the first byte is always 7f, the remaining three bytes represent ELF string.
  * ```02```: determines the arch ```01``` for 32-bit, and ```02``` for 64-bit, the class field tells same thing. 
    * For more information refer to [Wikipedia](https://en.wikipedia.org/wiki/Executable_and_Linkable_Format).
* One interesting field is ```Entry point address```, which tells where is the entry of the program (the memory address where the very first code to be executed).
  The address of **main** function is the default in a normal program, but it can be any function explicitly specifying the function name to gcc.
  
### Section header table

As it's said already, code and data compose a program. However, not
all types of code and data have the same purpose. For that reason, instead of a big chunk of code and data,
they are divided into smaller chunks, and each chunk must satisfy these condition:
  
  * Every section in an object file has exactly one section header describing it.
But, section headers may exist that do not have a section.
  * Each section occupies one contiguous (possibly empty) sequence of
    bytes within a file. That means, there’s no two regions of bytes that
    are the same section.
  * Sections in a file may not overlap. No byte in a file resides in more
    than one section.
  * An object file may have inactive space. The various headers and the
    sections might not “cover” every byte in an object file. The contents
    of the inactive data are unspecified.

Now ```readelf -S hello``` gives us:

```
There are 37 section headers, starting at offset 0x4710:

Section Headers:
  [Nr] Name              Type             Address           Offset
       Size              EntSize          Flags  Link  Info  Align
  [ 0]                   NULL             0000000000000000  00000000
       0000000000000000  0000000000000000           0     0     0
  [ 1] .interp           PROGBITS         0000000000000318  00000318
       000000000000001c  0000000000000000   A       0     0     1
  [ 2] .note.gnu.pr[...] NOTE             0000000000000338  00000338
       0000000000000040  0000000000000000   A       0     0     8
  [ 3] .note.gnu.bu[...] NOTE             0000000000000378  00000378
       0000000000000024  0000000000000000   A       0     0     4
  [ 4] .note.ABI-tag     NOTE             000000000000039c  0000039c
       0000000000000020  0000000000000000   A       0     0     4
  [ 5] .gnu.hash         GNU_HASH         00000000000003c0  000003c0
       000000000000001c  0000000000000000   A       6     0     8
  [ 6] .dynsym           DYNSYM           00000000000003e0  000003e0
       00000000000000a8  0000000000000018   A       7     1     8
  [ 7] .dynstr           STRTAB           0000000000000488  00000488
       000000000000008f  0000000000000000   A       0     0     1
  [ 8] .gnu.version      VERSYM           0000000000000518  00000518
       000000000000000e  0000000000000002   A       6     0     2
  [ 9] .gnu.version_r    VERNEED          0000000000000528  00000528
       0000000000000030  0000000000000000   A       7     1     8
  [10] .rela.dyn         RELA             0000000000000558  00000558
       00000000000000c0  0000000000000018   A       6     0     8
  [11] .rela.plt         RELA             0000000000000618  00000618
       0000000000000018  0000000000000018  AI       6    23     8
  [12] .init             PROGBITS         0000000000001000  00001000
       000000000000001b  0000000000000000  AX       0     0     4
  [13] .plt              PROGBITS         0000000000001020  00001020
       0000000000000020  0000000000000010  AX       0     0     16
  [14] .text             PROGBITS         0000000000001040  00001040
       0000000000000118  0000000000000000  AX       0     0     16
  [15] .fini             PROGBITS         0000000000001158  00001158
       000000000000000d  0000000000000000  AX       0     0     4
  [16] .rodata           PROGBITS         0000000000002000  00002000
       0000000000000012  0000000000000000   A       0     0     4
  [17] .eh_frame_hdr     PROGBITS         0000000000002014  00002014
       0000000000000024  0000000000000000   A       0     0     4
  [18] .eh_frame         PROGBITS         0000000000002038  00002038
       000000000000007c  0000000000000000   A       0     0     8
  [19] .init_array       INIT_ARRAY       0000000000003de8  00002de8
       0000000000000008  0000000000000008  WA       0     0     8
  [20] .fini_array       FINI_ARRAY       0000000000003df0  00002df0
       0000000000000008  0000000000000008  WA       0     0     8
  [21] .dynamic          DYNAMIC          0000000000003df8  00002df8
       00000000000001e0  0000000000000010  WA       7     0     8
  [22] .got              PROGBITS         0000000000003fd8  00002fd8
       0000000000000028  0000000000000008  WA       0     0     8
  [23] .got.plt          PROGBITS         0000000000004000  00003000
       0000000000000020  0000000000000008  WA       0     0     8
  [24] .data             PROGBITS         0000000000004020  00003020
       0000000000000010  0000000000000000  WA       0     0     8
  [25] .bss              NOBITS           0000000000004030  00003030
       0000000000000008  0000000000000000  WA       0     0     1
  [26] .comment          PROGBITS         0000000000000000  00003030
       000000000000001b  0000000000000001  MS       0     0     1
  [27] .debug_aranges    PROGBITS         0000000000000000  00003050
       00000000000000f0  0000000000000000           0     0     16
  [28] .debug_info       PROGBITS         0000000000000000  00003140
       0000000000000585  0000000000000000           0     0     1
  [29] .debug_abbrev     PROGBITS         0000000000000000  000036c5
       0000000000000198  0000000000000000           0     0     1
  [30] .debug_line       PROGBITS         0000000000000000  0000385d
       00000000000001da  0000000000000000           0     0     1
  [31] .debug_str        PROGBITS         0000000000000000  00003a37
       000000000000047a  0000000000000001  MS       0     0     1
  [32] .debug_line_str   PROGBITS         0000000000000000  00003eb1
       000000000000013e  0000000000000001  MS       0     0     1
  [33] .debug_rnglists   PROGBITS         0000000000000000  00003fef
       0000000000000042  0000000000000000           0     0     1
  [34] .symtab           SYMTAB           0000000000000000  00004038
       0000000000000378  0000000000000018          35    19     8
  [35] .strtab           STRTAB           0000000000000000  000043b0
       00000000000001e7  0000000000000000           0     0     1
  [36] .shstrtab         STRTAB           0000000000000000  00004597
       0000000000000176  0000000000000000           0     0     1
Key to Flags:
  W (write), A (alloc), X (execute), M (merge), S (strings), I (info),
  L (link order), O (extra OS processing required), G (group), T (TLS),
  C (compressed), x (unknown), o (OS specific), E (exclude),
  D (mbind), l (large), p (processor specific)
```

Note that the first line *There are 37 section headers, starting at offset 0x4710:* summarizes the total number of sections in the file,
and where the address where it starts.

```shell
  [Nr] Name              Type             Address           Offset
       Size              EntSize          Flags  Link  Info  Align
```

* **Nr** The index of each section.
* **Name** The name of each section.
* **Type** This field (in a section header) identifies the type of each section.
  Types are used to classify sections.
* **Address** The starting virtual address of each section. Note that the addresses
  are virtual only when a program runs in an OS with support for virtual memory enabled. (An OS addresses would all be physical)
* **Offset** is a distance in bytes, from the first byte of a file to the start of
  an object, such as a section or a segment in the context of an ELF binary file.
* **Size** The size in bytes of each section.
* **Flag** describes attributes of a section. Flags together with a type defines
  the purpose of a section. Two sections can be of the same type,
  but serve different purposes. For example, even though *.data* and *.text*
  share the same type, *.data* holds the initialized data of a program while
  *.text* holds executable instructions of a program. For that reason,
  *.data* is given read and write permission, but not executable.
  Any attempt to execute code in *.data* is denied by the running OS: in Linux,
  such invalid section usage gives a **segmentation fault**.

* **flags**
    
    | Flag | Description                                                                                                                                                                                                                                                                                                                                                                                   |
    |------|-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
    | w    | Bytes in this section are writable during execution.                                                                                                                                                                                                                                                                                                                                          |
    | A    | Memory is allocated for this section during process execution. Some control sections do not reside in the memory image of an object file; this attribute is off for those sections.                                                                                                                                                                                                           |
    | X    | The section contains executable instructions.                                                                                                                                                                                                                                                                                                                                                 |
    | M    | The data in the section may be merged to eliminate duplication. Each element in the section is compared against other elements in sections with the same name, type and flags. Elements that would have identical values at program run-time may be merged.                                                                                                                                   |
    | S    | The data elements in the section consist of null-terminated character strings. The size of each character is specified in the section header’s EntSize field.                                                                                                                                                                                                                                 |
    | l    | Specific large section for x86_64 architecture. This flag is not specified in the Generic ABI but in x86_64 ABI.                                                                                                                                                                                                                                                                              |
    | I    | The Info field of this section header holds an index of a section header. Otherwise, the number is the index of something else                                                                                                                                                                                                                                                                |
    | L    | Preserve section ordering when linking. If this section is combined with other sections in the output file, it must appear in the same relative order with respect to those sections, as the linked-to section appears with respect to sections the linked-to section is combined with. Apply when the Link field of this section’s header references another section (the linked-to section) |
    | G    | This section is a member (perhaps the only one) of a section group.                                                                                                                                                                                                                                                                                                                           |
    | T    | This section holds Thread-Local Storage, meaning that each thread has its own distinct instance of this data. A thread is a distinct execution flow of code. A program can have multiple threads that pack different pieces of code and execute separately, at the same time.                                                                                                                 |
    | E    | Link editor is to exclude this section from executable and shared library that it builds when those objects are not to be further relocated.                                                                                                                                                                                                                                                  |
    | x    | Unknown flag to readelf. It happens because the linking process can be done manually with a linker like GNU ld. That is, section flags can be specified manually, and some flags are for a customized ELF that the open-source readelf doesn’t know of.                                                                                                                                       |
    | O    | This section requires special OS-specific processing (beyond the standard linking rules) to avoid incorrect behavior. A link editor encounters sections whose headers contain OS-specific values it does not recognize by Type or Flags values defined by ELF standard, the link editor should combine those sections.                                                                        |
    | o    | All bits included in this flag are reserved for operating system-specific semantics.                                                                                                                                                                                                                                                                                                          |
    | P    | All bits included in this flag are reserved for processor-specific semantics. If meanings are specified, the processor supplement explains them.                                                                                                                                                                                                                                              |

* **Link and Info** are numbers that reference the indexes of sections, symbol table entries,
hash table entries. **Link** field only holds the index of a section, while **Info** field holds
the index of a section, a symbol table entry or a hash table entry, depends on the type of section.

* **Align** is a value that enforces the offset of a section should be divisible
  by the value. Only 0 and positive integral powers of two are allowed.
  Values 0 and 1 mean the section has no alignment constraint.

For instance:

```
[ 1] .interp           PROGBITS         0000000000000318  00000318
       000000000000001c  0000000000000000   A       0     0     1
```

The section name is `.interp`, and its type is `PROGBITS` which means it's part of the program.

`Address` is `0x0000000000400238`, which means the program is loaded
at this virtual memory address at runtime. 

`Offset` is `0x00000238` bytes into file.

`Size` is `0x000000000000001c` in bytes.

`EntSize` is `0`, which means this section does not have any fixed-size
entry.

`Flags` are `A` (Allocatable), which means this section consumes memory at runtime.

`Info and Link` are `0` and `0`, which means this section links to no section or entry in any table.

`Align` is `1`, which means no alignment.

### Section in-depth:

Sections are `.bss, .text, .data` etc. to examine the content of a section we would do
```shell
readelf -x <section name or section number> <file>
```

For example
```shell
readelf -x .bss hello
```
or
```shell
readelf -x 25 hello
```

* **NULL** marks a section header as inactive and does not have associated section.

```
[ 0]                   NULL             0000000000000000  00000000
       0000000000000000  0000000000000000           0     0     0
```

```shell
readelf -x 0 hello
```

```
Output:
Section '' has no data to dump.
```

* **NOTE** marks a section with special information that other programs will check for
  conformance, compatibility, etc, by a vendor or a system builder.

```
  [ 2] .note.gnu.pr[...] NOTE             0000000000000338  00000338
       0000000000000040  0000000000000000   A       0     0     8
  [ 3] .note.gnu.bu[...] NOTE             0000000000000378  00000378
       0000000000000024  0000000000000000   A       0     0     4
  [ 4] .note.ABI-tag     NOTE             000000000000039c  0000039c
       0000000000000020  0000000000000000   A       0     0     4
```

```shell
readelf -x 2 hello
```
```
output:
Hex dump of section '.note.gnu.property':
  0x00000338 04000000 30000000 05000000 474e5500 ....0.......GNU.
  0x00000348 028000c0 04000000 01000000 00000000 ................
  0x00000358 010001c0 04000000 01000000 00000000 ................
  0x00000368 020001c0 04000000 00000000 00000000 ................
```

* **PROGBITS** marks a section holding the main content of a program either code or data.

***
Cool note:
> .bss, stands for *Block Started by Symbol*
***

* **SYMTAB** and **DYNSYM** hold symbol table. A symbol table is an array of entries that describe symbols in a program.
A symbol is assigned to an entity in a program.
```
  [ 6] .dynsym           DYNSYM           00000000000003e0  000003e0
       00000000000000a8  0000000000000018   A       7     1     8
       
  [34] .symtab           SYMTAB           0000000000000000  00004038
       0000000000000378  0000000000000018          35    19     8
```

To show the symbol table:
```shell
readelf -s hello
```

```
Symbol table '.dynsym' contains 7 entries:
   Num:    Value          Size Type    Bind   Vis      Ndx Name
     0: 0000000000000000     0 NOTYPE  LOCAL  DEFAULT  UND 
     1: 0000000000000000     0 FUNC    GLOBAL DEFAULT  UND _[...]@GLIBC_2.34 (2)
     2: 0000000000000000     0 NOTYPE  WEAK   DEFAULT  UND _ITM_deregisterT[...]
     3: 0000000000000000     0 FUNC    GLOBAL DEFAULT  UND [...]@GLIBC_2.2.5 (3)
     4: 0000000000000000     0 NOTYPE  WEAK   DEFAULT  UND __gmon_start__
     5: 0000000000000000     0 NOTYPE  WEAK   DEFAULT  UND _ITM_registerTMC[...]
     6: 0000000000000000     0 FUNC    WEAK   DEFAULT  UND [...]@GLIBC_2.2.5 (3)

Symbol table '.symtab' contains 37 entries:
   Num:    Value          Size Type    Bind   Vis      Ndx Name
     0: 0000000000000000     0 NOTYPE  LOCAL  DEFAULT  UND 
     1: 0000000000000000     0 FILE    LOCAL  DEFAULT  ABS abi-note.c
     2: 000000000000039c    32 OBJECT  LOCAL  DEFAULT    4 __abi_tag
     3: 0000000000000000     0 FILE    LOCAL  DEFAULT  ABS init.c
     4: 0000000000000000     0 FILE    LOCAL  DEFAULT  ABS crtstuff.c
     5: 0000000000001070     0 FUNC    LOCAL  DEFAULT   14 deregister_tm_clones
     6: 00000000000010a0     0 FUNC    LOCAL  DEFAULT   14 register_tm_clones
     7: 00000000000010e0     0 FUNC    LOCAL  DEFAULT   14 __do_global_dtors_aux
     8: 0000000000004030     1 OBJECT  LOCAL  DEFAULT   25 completed.0
     9: 0000000000003df0     0 OBJECT  LOCAL  DEFAULT   20 __do_global_dtor[...]
    10: 0000000000001130     0 FUNC    LOCAL  DEFAULT   14 frame_dummy
    11: 0000000000003de8     0 OBJECT  LOCAL  DEFAULT   19 __frame_dummy_in[...]
    12: 0000000000000000     0 FILE    LOCAL  DEFAULT  ABS hello.c
    13: 0000000000000000     0 FILE    LOCAL  DEFAULT  ABS crtstuff.c
    14: 00000000000020b0     0 OBJECT  LOCAL  DEFAULT   18 __FRAME_END__
    15: 0000000000000000     0 FILE    LOCAL  DEFAULT  ABS 
    16: 0000000000003df8     0 OBJECT  LOCAL  DEFAULT   21 _DYNAMIC
    17: 0000000000002014     0 NOTYPE  LOCAL  DEFAULT   17 __GNU_EH_FRAME_HDR
    18: 0000000000004000     0 OBJECT  LOCAL  DEFAULT   23 _GLOBAL_OFFSET_TABLE_
    19: 0000000000000000     0 FUNC    GLOBAL DEFAULT  UND __libc_start_mai[...]
    20: 0000000000000000     0 NOTYPE  WEAK   DEFAULT  UND _ITM_deregisterT[...]
    21: 0000000000004020     0 NOTYPE  WEAK   DEFAULT   24 data_start
    22: 0000000000004030     0 NOTYPE  GLOBAL DEFAULT   24 _edata
    23: 0000000000001158     0 FUNC    GLOBAL HIDDEN    15 _fini
    24: 0000000000000000     0 FUNC    GLOBAL DEFAULT  UND printf@GLIBC_2.2.5
    25: 0000000000004020     0 NOTYPE  GLOBAL DEFAULT   24 __data_start
    26: 0000000000000000     0 NOTYPE  WEAK   DEFAULT  UND __gmon_start__
    27: 0000000000004028     0 OBJECT  GLOBAL HIDDEN    24 __dso_handle
    28: 0000000000002000     4 OBJECT  GLOBAL DEFAULT   16 _IO_stdin_used
    29: 0000000000004038     0 NOTYPE  GLOBAL DEFAULT   25 _end
    30: 0000000000001040    38 FUNC    GLOBAL DEFAULT   14 _start
    31: 0000000000004030     0 NOTYPE  GLOBAL DEFAULT   25 __bss_start
    32: 0000000000001139    31 FUNC    GLOBAL DEFAULT   14 main
    33: 0000000000004030     0 OBJECT  GLOBAL HIDDEN    24 __TMC_END__
    34: 0000000000000000     0 NOTYPE  WEAK   DEFAULT  UND _ITM_registerTMC[...]
    35: 0000000000000000     0 FUNC    WEAK   DEFAULT  UND __cxa_finalize@G[...]
    36: 0000000000001000     0 FUNC    GLOBAL HIDDEN    12 _init
```

Note, there are two sections as it's said, `.dynsym`, `.symtab`.

* `Num` is the index of an entry in a table.

* `Value` is the virtual memory address where the symbol is located.

* `Size` is the size of the entity associated with a symbol.

* `Type` is a symbol type according to table.

* `NOTYPE` The type of symbol is not specified.

* `OBJECT` The symbol is associated with a data object. In C, any variable definition is of OBJECT type.

* `FUNC` The symbol is associated with a function or other executable
code.

* `SECTION` The symbol is associated with a section, and exists primarily for relocation.

* `FILE` The symbol is the name of a source file associated with an
executable binary.

* `COMMON` The symbol labels an uninitialized variable. That is, when
a variable in C is defined as global variable without an initial
value, or as an external variable using the extern keyword. In
other words, these variables stay in .bss section.

* `Bind` is the scope of a symbol.
  * `LOCAL` are symbols that are only visible in the object files that
    defined them. like static variable/function in C.
Example:
```c
// static.c
// gcc -o static static.c

#include <stdio.h>

static void static_print()
{
	printf("Hello, static!\n");
}

int main()
{
	static int static_var = 0;

	static_print();
	return 0x0;
}
```

```shell
readelf -s static
```

```
Symbol table '.dynsym' contains 7 entries:
   Num:    Value          Size Type    Bind   Vis      Ndx Name
     0: 0000000000000000     0 NOTYPE  LOCAL  DEFAULT  UND 
     1: 0000000000000000     0 FUNC    GLOBAL DEFAULT  UND _[...]@GLIBC_2.34 (2)
     2: 0000000000000000     0 NOTYPE  WEAK   DEFAULT  UND _ITM_deregisterT[...]
     3: 0000000000000000     0 FUNC    GLOBAL DEFAULT  UND puts@GLIBC_2.2.5 (3)
     4: 0000000000000000     0 NOTYPE  WEAK   DEFAULT  UND __gmon_start__
     5: 0000000000000000     0 NOTYPE  WEAK   DEFAULT  UND _ITM_registerTMC[...]
     6: 0000000000000000     0 FUNC    WEAK   DEFAULT  UND [...]@GLIBC_2.2.5 (3)

Symbol table '.symtab' contains 39 entries:
   Num:    Value          Size Type    Bind   Vis      Ndx Name
     0: 0000000000000000     0 NOTYPE  LOCAL  DEFAULT  UND 
     1: 0000000000000000     0 FILE    LOCAL  DEFAULT  ABS abi-note.c
     2: 000000000000039c    32 OBJECT  LOCAL  DEFAULT    4 __abi_tag
     3: 0000000000000000     0 FILE    LOCAL  DEFAULT  ABS init.c
     4: 0000000000000000     0 FILE    LOCAL  DEFAULT  ABS crtstuff.c
     5: 0000000000001070     0 FUNC    LOCAL  DEFAULT   14 deregister_tm_clones
     6: 00000000000010a0     0 FUNC    LOCAL  DEFAULT   14 register_tm_clones
     7: 00000000000010e0     0 FUNC    LOCAL  DEFAULT   14 __do_global_dtors_aux
     8: 0000000000004030     1 OBJECT  LOCAL  DEFAULT   25 completed.0
     9: 0000000000003df0     0 OBJECT  LOCAL  DEFAULT   20 __do_global_dtor[...]
    10: 0000000000001130     0 FUNC    LOCAL  DEFAULT   14 frame_dummy
    11: 0000000000003de8     0 OBJECT  LOCAL  DEFAULT   19 __frame_dummy_in[...]
    12: 0000000000000000     0 FILE    LOCAL  DEFAULT  ABS static.c
    13: 0000000000001139    22 FUNC    LOCAL  DEFAULT   14 static_print
    14: 0000000000004034     4 OBJECT  LOCAL  DEFAULT   25 static_var.0
    15: 0000000000000000     0 FILE    LOCAL  DEFAULT  ABS crtstuff.c
    16: 00000000000020d8     0 OBJECT  LOCAL  DEFAULT   18 __FRAME_END__
    17: 0000000000000000     0 FILE    LOCAL  DEFAULT  ABS 
    18: 0000000000003df8     0 OBJECT  LOCAL  DEFAULT   21 _DYNAMIC
    19: 0000000000002014     0 NOTYPE  LOCAL  DEFAULT   17 __GNU_EH_FRAME_HDR
    20: 0000000000004000     0 OBJECT  LOCAL  DEFAULT   23 _GLOBAL_OFFSET_TABLE_
    21: 0000000000000000     0 FUNC    GLOBAL DEFAULT  UND __libc_start_mai[...]
    22: 0000000000000000     0 NOTYPE  WEAK   DEFAULT  UND _ITM_deregisterT[...]
    23: 0000000000004020     0 NOTYPE  WEAK   DEFAULT   24 data_start
    24: 0000000000000000     0 FUNC    GLOBAL DEFAULT  UND puts@GLIBC_2.2.5
    25: 0000000000004030     0 NOTYPE  GLOBAL DEFAULT   24 _edata
    26: 0000000000001164     0 FUNC    GLOBAL HIDDEN    15 _fini
    27: 0000000000004020     0 NOTYPE  GLOBAL DEFAULT   24 __data_start
    28: 0000000000000000     0 NOTYPE  WEAK   DEFAULT  UND __gmon_start__
    29: 0000000000004028     0 OBJECT  GLOBAL HIDDEN    24 __dso_handle
    30: 0000000000002000     4 OBJECT  GLOBAL DEFAULT   16 _IO_stdin_used
    31: 0000000000004038     0 NOTYPE  GLOBAL DEFAULT   25 _end
    32: 0000000000001040    38 FUNC    GLOBAL DEFAULT   14 _start
    33: 0000000000004030     0 NOTYPE  GLOBAL DEFAULT   25 __bss_start
    34: 000000000000114f    21 FUNC    GLOBAL DEFAULT   14 main
    35: 0000000000004030     0 OBJECT  GLOBAL HIDDEN    24 __TMC_END__
    36: 0000000000000000     0 NOTYPE  WEAK   DEFAULT  UND _ITM_registerTMC[...]
    37: 0000000000000000     0 FUNC    WEAK   DEFAULT  UND __cxa_finalize@G[...]
    38: 0000000000001000     0 FUNC    GLOBAL HIDDEN    12 _init
```

Note:
```
    13: 0000000000001139    22 FUNC    LOCAL  DEFAULT   14 static_print
    14: 0000000000004034     4 OBJECT  LOCAL  DEFAULT   25 static_var.0
```

* `LOCAL` are symbols that are only visible in the object files that
 defined them. like static variable/function in C.