#ifndef WPACKER_H
#define WPACKER_H
# ifndef BONUS
#  define EHDR Elf64_Ehdr
#  define SHDR Elf64_Shdr
#  define PHDR Elf64_Phdr
#  define UINT uint64_t
# else
#  define EHDR Elf32_Ehdr
#  define SHDR Elf32_Shdr
#  define PHDR Elf32_Phdr
#  define UINT uint32_t
# endif

// STDS
#include <fcntl.h>
#include <stdio.h>
#include <sys/mman.h>
#include <elf.h>
#include <errno.h>

#include "libft.h"

# define KEY_SIZE	8




extern unsigned char	patch[];
extern unsigned int		patch_len;

typedef struct t_elf {
	EHDR*	ehdr;
	PHDR*	phdr;
	PHDR*	code_segment;
	SHDR*	shdr;
	SHDR*	text_section;
	char*		mmap_ptr;
	ssize_t		len;
}	t_elf;

typedef struct s_patch {
	UINT o_entry;
	UINT code;
	UINT code_size;
	UINT key;
	UINT new_entry;
} t_patch;

int init_struct(char *file, char** data);
void init_x64_86_struct(char *data, t_elf *ctx, ssize_t len);

PHDR* get_x64_86_code_segment(t_elf *ctx);
SHDR* get_x64_86_text_section(t_elf *ctx);

int pack_elf(char *file);
int inject_elf(t_elf *ctx);

#endif
