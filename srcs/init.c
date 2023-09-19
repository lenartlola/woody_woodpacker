#include <wpacker.h>

t_elf* init_struct(char *file)
{
	t_elf	*ctx;
	char*	_data;
	int		fd;
	int		s;

	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		ft_printf(2, "Failed t open file %s\n", file);
		return NULL;
	}
	
	s = lseek(fd, 0, SEEK_END);
	if (s == -1) 
	{
		ft_printf(2, "Error happened in lseek %s\n", strerror(errno));
		close(fd);
		return NULL;
	}
	
	_data = mmap(NULL, (size_t)s, PROT_READ, MAP_SHARED, fd, 0);
	if (_data == MAP_FAILED)
	{
		ft_printf(2, "Error happened while mapping memory %s\n", strerror(errno));
		close(fd);
		return NULL;
	}

	if (_data[EI_CLASS] != ELFCLASS64)
	{
		ft_printf(2, "Error: invalid ELF file\n");
		close(fd);

		if (munmap(_data, (size_t)s) == -1)
			ft_printf(2, "Error happened while unmaping memory: %s", strerror(errno));
		return NULL;
	}

	ctx = (t_elf *) malloc(sizeof(t_elf));
	ctx->mmap_ptr = _data;
	ctx->ehdr = (Elf64_Ehdr *)_data;
	ctx->phdr = (Elf64_Phdr *)_data;
	ctx->shdr = (Elf64_Shdr *)_data;
	ctx->len = (size_t)s;
	close(fd);
	return ctx;
}
