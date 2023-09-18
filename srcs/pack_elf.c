#include <wpacker.h>

int pack_elf64(t_elf* ctx)
{
	Elf64_Ehdr *ehdr;

	ehdr = (Elf64_Ehdr *)ctx->mmap_ptr;
	
	ft_printf(0, "Ident: %2x %2x %2x %2x\n", ehdr->e_ident[0], ehdr->e_ident[1], ehdr->e_ident[2], ehdr->e_ident[3]);
	return 0;
}

int pack_elf(char *file)
{
	t_elf	ctx;

	if (init_struct(file, &ctx))
		return 1;	

	if (ctx.mmap_ptr[EI_CLASS] == ELFCLASS64)
	{
		pack_elf64(&ctx);
	}

	if (munmap(ctx.mmap_ptr, ctx.len) == -1)
	{
		ft_printf(2, "Error happened while unmaping memory: %s", strerror(errno));
		return 1;
	}
	return 0;
}
