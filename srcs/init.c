#include <wpacker.h>

t_elf* init_struct(char *file)
{
	t_elf	*ctx;
	char*	_data;
	int		fd;
	off_t	s;

	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		ft_printf(2, "Failed t open file %s, REASON: %s\n", file, strerror(errno));
		return NULL;
	}
	
	s = lseek(fd, 0, SEEK_END);
	if (s == -1) 
	{
		ft_printf(2, "Error happened in lseek, REASON: %s\n", strerror(errno));
		close(fd);
		return NULL;
	}
	
    _data = mmap(NULL, s, PROT_READ | PROT_WRITE, MAP_PRIVATE, fd, 0);
	if (_data == MAP_FAILED)
	{
		ft_printf(2, "Error happened while mapping memory, REASON: %s\n", strerror(errno));
		close(fd);
		return NULL;
	}

	if (_data[EI_CLASS] != ELFCLASS64)
	{
		ft_printf(2, "Error: invalid ELF file\n");
		close(fd);

		if (munmap(_data, s) == -1)
			ft_printf(2, "Error happened while unmaping memory, REASON: %s", strerror(errno));
		return NULL;
	}

	ctx = (t_elf *) malloc(sizeof(t_elf));
	ctx->mmap_ptr = _data;
	ctx->ehdr = (Elf64_Ehdr *)_data;
	ctx->phdr = (Elf64_Phdr *)((char *)_data + ctx->ehdr->e_phoff);
	ctx->shdr = (Elf64_Shdr *)((char *)_data + ctx->ehdr->e_shoff);
	ctx->len = s;
	close(fd);
	return ctx;
}
