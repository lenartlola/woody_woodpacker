#include <wpacker.h>

static unsigned int
get_random(size_t size) {
	int fd;
	long long rnd;

	fd = open("/dev/urandom", O_RDONLY);
	if (fd < 0)
	{
		ft_printf(2, "[-] Error couldn't open fd\n");
		return -1;
	}
	rnd = read(fd, &rnd, size);
	//if (rnd < 0)
	//{
	//	ft_printf(2, "[-] Failed to read from /dev/urandom\n");
	//	return -1;
	//}
	close(fd);
	return (uint64_t)rnd;
}

Elf64_Shdr*
get_text_section(t_elf *ctx) {
	char *section_names;

	section_names = (char *)ctx->mmap_ptr + ctx->shdr[ctx->ehdr->e_shstrndx].sh_offset;
	for (int i = 0; i < ctx->ehdr->e_shnum; i++) {
		if ((!ft_strncmp(".text", section_names + ctx->shdr[i].sh_name, 6))
			&& (ctx->shdr[i].sh_type == SHT_PROGBITS)
			&& (ctx->shdr[i].sh_flags & SHF_EXECINSTR))
		{
			return &ctx->shdr[i];
		}
	}
	return NULL;
}

Elf64_Phdr*
get_code_segment(t_elf *ctx)
{
	for (int i = 0; i < ctx->ehdr->e_phnum; i++) {
		if ((ctx->phdr[i].p_type == PT_LOAD)
			&& (ctx->phdr[i].p_vaddr <= ctx->ehdr->e_entry)
			&& (ctx->phdr[i].p_vaddr + ctx->phdr[i].p_memsz > ctx->ehdr->e_entry))
		{
			return &ctx->phdr[i];
		}
	}
	return NULL;
}

static void
encrypt_elf(size_t size, void *data, unsigned int key)
{
	uint64_t byte;

	for (size_t i = 0; i < size; i++) {
		*(unsigned char*)(data + i) = *(unsigned char *)(data + i) ^ (key & 0b11111111);
		byte = key & 0b0000001;
		byte <<= 63;
		key = (key >> 1) | byte;
	}
}

static void
set_new_entry(t_patch *patch_ctx, t_elf *ctx, Elf64_Phdr* code_segment)
{
	void *ptr;
	ssize_t len;
	
	ptr = ctx->mmap_ptr + code_segment->p_offset + code_segment->p_filesz;
	code_segment->p_memsz += patch_len;
	code_segment->p_filesz += patch_len;
	code_segment->p_flags = code_segment->p_flags | PF_W;
	len = patch_len - sizeof(t_patch);
	ft_memmove(ptr, patch, len);
	ft_memmove(ptr + len, patch_ctx, sizeof(t_patch));
}

static int
write_elf(t_elf *ctx)
{
	int fd;
	void* ptr;
	size_t i;

	fd = open("./woody", O_WRONLY | O_CREAT | O_TRUNC, 0755);
	if (fd < 0)
	{
		ft_printf(2, "[-] Failed to create woody file'n");
		return -1;
	}
	ptr = ctx->mmap_ptr;
	i = 0;
	while (i < ctx->len) {
		ptr = ctx->mmap_ptr + i;
		if (ctx->len - i >= 4096) {
			i += write(fd, ptr, 4096);
		} else {
			i += write(fd, ptr, ctx->len % 4096);
		}
	}
	close(fd);
	return i;
}    

int
inject_elf(t_elf *ctx)
{
	t_patch patch_ctx;
	Elf64_Ehdr* patch_ehdr;
	Elf64_Shdr* text_section;
	Elf64_Phdr* code_segment;

	patch_ehdr = (Elf64_Ehdr *)ctx->mmap_ptr;
	text_section = get_text_section(ctx);
	if (text_section == NULL)
	{
		ft_printf(2, "[-] Error, no text section found\n");
		return -1;
	}
	code_segment = get_code_segment(ctx);
	if (code_segment == NULL)
	{
		ft_printf(2, "[-] Error, no loadable code segment found\n");
		return -1;
	}
	patch_ehdr->e_entry = code_segment->p_vaddr + code_segment->p_memsz;
	ft_memset(&patch_ctx, 0, sizeof(t_patch));
	patch_ctx.key = get_random(8);
	patch_ctx.o_entry = ctx->ehdr->e_entry;
	patch_ctx.code = text_section->sh_addr;
	patch_ctx.code_size = text_section->sh_size;
	patch_ctx.new_entry = patch_ehdr->e_entry;
	encrypt_elf(text_section->sh_size, ctx->mmap_ptr + text_section->sh_offset, patch_ctx.key);
	set_new_entry(&patch_ctx, ctx, code_segment);
	write_elf(ctx);
	
	return 0;
}

