#include <wpacker.h>

static int
elf_sanitizer(char *data)
{
	if (data[0] != 0x7f || data[1] != 'E' || data[2] != 'L' || data[3] != 'F') {
		ft_printf(2, "[-] Elf magic header doesn't match: 0x%x%c%c%c\n", data[0], data[1], data[2], data[3]);
		return 1;
	}
	if (data[4] != 1 && data[4] != 2) {
		ft_printf(2, "[-] Invalid architecture 0x%x\n", data[4]);
		return 1;
	}
	if (data[16] != ET_EXEC && data[16] != ET_DYN) {
		ft_printf(2, "[-] Invalid type of ELF. Must be either executable or shared\n");
		return 1;
	}
	return 0;
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
get_x64_86_segments(char *data, t_elf *ctx)
{
	ctx->ehdr = (Elf64_Ehdr *)data;
	ctx->phdr = (Elf64_Phdr *)((char *)data + ctx->ehdr->e_phoff);
	ctx->shdr = (Elf64_Shdr *)((char *)data + ctx->ehdr->e_shoff);
	ctx->code_segment = get_code_segment(ctx);
	ctx->text_section = get_text_section(ctx);
}

int
init_struct(char *file, t_elf *ctx)
{
	char*	_data;
	int		fd;
//	off_t	s;

	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		ft_printf(2, "Failed t open file %s, REASON: %s\n", file, strerror(errno));
		return 1;
	}
	
	ctx->len = lseek(fd, (size_t)0, SEEK_END);
	if (ctx->len == -1)
	{
		ft_printf(2, "Error happened in lseek, REASON: %s\n", strerror(errno));
		close(fd);
		return 1;
	}
	
    _data = mmap(NULL, ctx->len, PROT_READ | PROT_WRITE, MAP_PRIVATE, fd, (size_t)0);
	if (_data == MAP_FAILED)
	{
		ft_printf(2, "Error happened while mapping memory, REASON: %s\n", strerror(errno));
		close(fd);
		return 1;
	}

	if (elf_sanitizer(_data) != 0)
	{
		ft_printf(2, "[-] Error: invalid ELF file\n");
		close(fd);

		if (munmap(_data, ctx->len) == -1)
			ft_printf(2, "[-] Error happened while unmaping memory, REASON: %s", strerror(errno));
		return 1;	
	}
	
	ctx->mmap_ptr = _data;
	if (_data[4] == 2) {
		get_x64_86_segments(_data, ctx);
	}
	else if (_data[4] == 1) {
		ft_printf(2, "[!] TODO 32 bit arch\n");
		return 1;
	}
//	ctx->len = s;
	close(fd);
	return 0;
}
