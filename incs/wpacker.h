#ifndef WPACKER_H
#define WPACKER_H

// STDS
#include <fcntl.h>
#include <stdio.h>
#include <sys/mman.h>
#include <elf.h>
#include <errno.h>

#include "libft.h"

typedef struct s_elf {
	Elf64_Ehdr*	ehdr;
	Elf64_Phdr*	phdr;
	Elf64_Shdr*	shdr;
	char*		mmap_ptr;
	size_t		len;
}	t_elf;


t_elf* init_struct(char *file);
int pack_elf(char *file);

#endif
