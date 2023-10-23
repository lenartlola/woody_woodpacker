#include <wpacker.h>

int pack_elf(char *file)
{
	char *data;
	//t_elf	ctx;
	ssize_t len;
	
	//ft_memset(&ctx, 0, sizeof(t_elf));
	len = init_struct(file, &data);
	if (len < 0)
		return 1;
	if (data[4] == 2) {
		t_elf64 ctx;
		ft_memset(&ctx, 0, sizeof(t_elf64));
		ctx.mmap_ptr = data;
		ctx.len = len;
		ctx.ehdr = (Elf64_Ehdr *)data;
		ctx.phdr = (Elf64_Phdr *)((char *)data + ctx.ehdr->e_phoff);
		ctx.shdr = (Elf64_Shdr *)((char *)data + ctx.ehdr->e_shoff);
		ctx.code_segment = get_x64_86_code_segment(&ctx);
		ctx.text_section = get_x64_86_text_section(&ctx);
		inject_elf(&ctx);
		//init_x64_86_struct(data, &ctx, len);
	}
	//inject_elf(&ctx);
	//if (munmap(ctx.mmap_ptr, ctx.len) == -1)
	//{
	//	ft_printf(2, "Error happened while unmaping memory: %s", strerror(errno));
	//	return 1;
	//}
	return 0;
}
