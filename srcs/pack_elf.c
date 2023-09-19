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
	t_elf	*ctx;

	ctx = init_struct(file);
	if (ctx == NULL)
		return 1;

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
