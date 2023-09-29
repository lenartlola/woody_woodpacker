#include <wpacker.h>

/*
 * This shellcode will write ....WOODY.... followed by a newline to the stdout.
 * For more information look at write.asm file
 */
char shellcode[] = "\xbf\x00\x00\x00\x00\x48\x8d\x35\x13\x00\x00\x00\xba\x0e\x00\x00\x00\xb8\x01\x00\x00\x00\x0f\x05\xb8\x3c\x00\x00\x00\x0f\x05\x2e\x2e\x2e\x2e\x57\x4f\x4f\x44\x59\x2e\x2e\x2e\x2e\x0a";


int pack_elf64(t_elf* ctx)
{
	Elf64_Ehdr *ehdr;

	ehdr = (Elf64_Ehdr *)ctx->mmap_ptr;
	
	ft_printf(0, "Ident: %2x %2x %2x %2x\n", ehdr->e_ident[0], ehdr->e_ident[1], ehdr->e_ident[2], ehdr->e_ident[3]);
	return 0;
}

void	extract_segment(t_elf* ctx, uint64_t* new_entry, uint64_t* text_segment_end, uint64_t* gap)
{
    int	i;

    i = 0;
	// Iterate over every entry
	while (i < ctx->ehdr->e_phnum) {
		// PT_LOAD segments are loaded to memory, so we need to inject the new entry_point there.
		if (ctx->phdr[i].p_type == PT_LOAD)
		{
			// Make the segment writable
            ctx->phdr[i].p_flags |= PF_W;
			if (ctx->phdr[i].p_flags == (PF_W | PF_X | PF_R))
			{
				// virtual address + filessz gives the new address where the code will be injected
				*new_entry = ctx->phdr[i].p_vaddr + ctx->phdr[i].p_filesz;
				*text_segment_end = ctx->phdr[i].p_filesz;
			}
			else if (ctx->phdr[i].p_flags == (PF_R | PF_W))
			{
				*gap = ctx->phdr[i].p_offset - *text_segment_end;
			}
		}
        i++;
	}
}

int	parse_text_section(t_elf* ctx, uint64_t* text_section_init,
						   uint64_t* text_section_end, uint64_t* text_section_size)
{
	int i;
	char *section_mem;

	i = 0;
	if (ctx->ehdr->e_shnum == 0 || ctx->ehdr->e_shstrndx == 0)
	{
		return 1;
	}
	section_mem = (char *)ctx->ehdr + ctx->shdr[ctx->ehdr->e_shstrndx].sh_offset;
	while (i < ctx->ehdr->e_shnum)
	{
		if (strncmp(&section_mem[ctx->shdr[i].sh_name], ".text", ft_strlen(".text")) == 0)
		{
			*text_section_init = ctx->shdr[i].sh_offset;
			*text_section_size = ctx->shdr[i].sh_size;
			*text_section_end = *text_section_init + *text_section_size;
			return 0;
		}
		i++;
	}

	return 0;
}

static int inject_payload(t_elf* ctx)
{
	/*
	 * We need to track the entry point of the program,
	 * as we modify it we later need to reset its new entry point.
	 * In the elf header there is; `ElfN_Addr e_entry` which 
	 * gives the virtual address to which the system first transfers control, 
	 * thus starting the process.
	 */
	Elf64_Addr	orig_entry = ctx->ehdr->e_entry;
	Elf64_Xword	new_entry = 0;
	uint64_t	text_segment_end = 0;
	uint64_t	text_section_end = 0;
	uint64_t	text_section_size = 0;
	uint64_t	text_section_init = 0;
	uint64_t	gap = 0;
//	long		shellcode_size = sizeof(shellcode);
//	short		is_static;

	ft_printf(0, "[+] original entry point: %p\n", &orig_entry);
	extract_segment(ctx, &new_entry, &text_segment_end, &gap);
	ft_printf(0, "[+] found entry point: %p\n", &new_entry);
	ft_printf(0, "[+] available gap space: %d\n", gap);

	if (parse_text_section(ctx, &text_section_init, &text_section_end, &text_section_size))
	{
		ft_printf(0, "[-] failed to parse text section\n");
		return 1;
	}

	return 0;
}

int pack_elf(char *file)
{
	t_elf	*ctx;

	ctx = init_struct(file);
	if (ctx == NULL)
		return 1;

	inject_payload(ctx);

	if (munmap(ctx->mmap_ptr, ctx->len) == -1)
	{
		ft_printf(2, "Error happened while unmaping memory: %s", strerror(errno));
		free(ctx);
		ctx = NULL;
		return 1;
	}
	free(ctx);
	ctx = NULL;
	return 0;
}
