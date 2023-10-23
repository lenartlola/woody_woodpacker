#include <wpacker.h>

Elf64_Shdr*
get_x64_86_text_section(t_elf64 *ctx) {
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
get_x64_86_code_segment(t_elf64 *ctx)
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
