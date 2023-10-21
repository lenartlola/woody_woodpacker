#include <wpacker.h>

int pack_elf(char *file)
{
	t_elf	ctx;

	ft_memset(&ctx, 0, sizeof(t_elf));
	if (init_struct(file, &ctx) != 0)
		return 1;
	inject_elf(&ctx);
	if (munmap(ctx.mmap_ptr, ctx.len) == -1)
	{
		ft_printf(2, "Error happened while unmaping memory: %s", strerror(errno));
		return 1;
	}
	return 0;
}
