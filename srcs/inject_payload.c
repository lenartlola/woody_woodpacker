#include <wpacker.h>

static UINT
get_random(size_t size) {
	int fd;
	long long rnd;

	fd = open("/dev/urandom", O_RDONLY);
	if (fd < 0)
	{
		ft_printf(2, "[-] Error couldn't open fd\n");
		return -1;
	}
	rnd = 0;
	read(fd, &rnd, size);
	ft_printf(1, "Key: 0x%#lX\n", rnd);
	close(fd);
	return ((UINT)rnd);
}

static void
encrypt_elf(size_t size, void *data, UINT key)
{
	UINT byte;
	int shft;

	#ifdef BONUS
		shft = 31;
	#else
		shft = 63;
	#endif
	for (size_t i = 0; i < size; ++i) {
		*(unsigned char*)(data + i) = *(unsigned char *)(data + i) ^ (key & 0b11111111);
		byte = key & 0b0000001;
		byte <<= shft;
		key = (key >> 1) | byte;
	}
}

static void
set_new_entry(t_patch *patch_ctx, t_elf *ctx)
{
	void *ptr;
	ssize_t len;

	ptr = ctx->mmap_ptr + ctx->code_segment->p_offset + ctx->code_segment->p_filesz;
	ctx->code_segment->p_memsz += patch_len;
	ctx->code_segment->p_filesz += patch_len;
	ctx->code_segment->p_flags = ctx->code_segment->p_flags | PF_W;
	len = patch_len - sizeof(t_patch);
	ft_memmove(ptr, patch, len);
	ft_memmove(ptr + len, patch_ctx, sizeof(t_patch));
}

static ssize_t
write_elf(t_elf *ctx)
{
	int fd;
	void* ptr;
	ssize_t i;

	fd = open("./woody", O_WRONLY | O_CREAT | O_TRUNC, 0755);
	if (fd < 0)
	{
		ft_printf(2, "[-] Failed to create woody file\n");
		return -1;
	}
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
	EHDR* patch_ehdr;

	patch_ehdr = (EHDR *)ctx->mmap_ptr;

	ft_memset(&patch_ctx, 0, sizeof(t_patch));
	patch_ctx.key = get_random(8);
	patch_ctx.o_entry = ctx->ehdr->e_entry;
	patch_ctx.code = ctx->text_section->sh_addr;
	patch_ctx.code_size = ctx->text_section->sh_size;
	patch_ehdr->e_entry = ctx->code_segment->p_vaddr + ctx->code_segment->p_memsz;
	patch_ctx.new_entry = patch_ehdr->e_entry;
	void *pos = ctx->mmap_ptr + ctx->text_section->sh_offset;
	encrypt_elf(ctx->text_section->sh_size, pos, patch_ctx.key);
	set_new_entry(&patch_ctx, ctx);
	write_elf(ctx);
	return 0;
}

