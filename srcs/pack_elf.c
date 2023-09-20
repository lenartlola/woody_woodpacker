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

static int inject_payload(t_elf* ctx)
{
	/*
	 * We need to track the entry point of the program,
	 * as we modify it we later need to reset its new entry point.
	 * In the elf header there is; `ElfN_Addr e_entry` which 
	 * gives the virtual address to which the system first transfers control, 
	 * thus starting the process.
	 */
	Elf64_Addr orig_entry = ctx->ehdr->e_entry;
	uint64_t payload_size = sizeof(shellcode);
	ft_printf(0, "entry point: %lx, %ld\n", orig_entry, payload_size);

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
