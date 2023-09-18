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
	char*		mmap_ptr;
	//Elf64_Ehdr*	ehdr;
	size_t		len;
}	t_elf;


int init_struct(char *file, t_elf *ctx);
int pack_elf(char *file);

#endif
