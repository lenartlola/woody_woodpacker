#ifndef WPACKER_H
#define WPACKER_H

// STDS
#include <fcntl.h>
#include <stdio.h>
#include <sys/mman.h>
#include <elf.h>
#include <errno.h>

#include "libft.h"

extern unsigned char	patch[];
extern unsigned int		patch_len;

typedef struct s_elf {
	Elf64_Ehdr*	ehdr;
	Elf64_Phdr*	phdr;
	Elf64_Shdr*	shdr;
	char*		mmap_ptr;
	size_t		len;
}	t_elf;

typedef struct s_patch {
	unsigned int o_entry;
	unsigned int code;
	unsigned int code_size;
	unsigned int key;
	unsigned int new_entry;
} t_patch;

int init_struct(char *file, t_elf *ctx);
int pack_elf(char *file);
int inject_elf(t_elf *ctx);

#endif
