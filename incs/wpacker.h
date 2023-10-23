#ifndef WPACKER_H
#define WPACKER_H

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

typedef struct s_elf64 {
	Elf64_Ehdr*	ehdr;
	Elf64_Phdr*	phdr;
	Elf64_Phdr*	code_segment;
	Elf64_Shdr*	shdr;
	Elf64_Shdr*	text_section;
	char*		mmap_ptr;
	ssize_t		len;
}	t_elf64;

typedef struct s_elf32 {
	Elf32_Ehdr*	ehdr;
	Elf32_Phdr*	phdr;
	Elf32_Phdr*	code_segment;
	Elf32_Shdr*	shdr;
	Elf32_Shdr*	text_section;
	char*		mmap_ptr;
	ssize_t		len;
}	t_elf32;

typedef struct s_patch64 {
	uint64_t o_entry;
	uint64_t code;
	uint64_t code_size;
	uint64_t key;
	uint64_t new_entry;
} t_patch64;

typedef struct s_patch32 {
	uint32_t o_entry;
	uint32_t code;
	uint32_t code_size;
	uint32_t key;
	uint32_t new_entry;
} t_patch32;

int init_struct(char *file, char** data);
void init_x64_86_struct(char *data, t_elf64 *ctx, ssize_t len);

Elf64_Phdr* get_x64_86_code_segment(t_elf64 *ctx);
Elf64_Shdr* get_x64_86_text_section(t_elf64 *ctx);

int pack_elf(char *file);
int inject_elf(t_elf64 *ctx);

#endif
