#include <wpacker.h>

int init_struct(char *file, t_elf *ctx)
{
	char*	_data;
	int		fd;
	int		s;

	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		ft_printf(2, "Failed t open file %s\n", file);
		return 1;
	}
	s = lseek(fd, 0, SEEK_END);
	if (s == -1) 
	{
		ft_printf(2, "Error happened in lseek %s\n", strerror(errno));
		close(fd);
		return 1;
	}
	ctx->len = (size_t)s;
	_data = mmap(NULL, ctx->len, PROT_READ, MAP_SHARED, fd, 0);
	if (_data == MAP_FAILED)
	{
		ft_printf(2, "Error happened while mapping memory %s\n", strerror(errno));
		close(fd);
		return 1;
	}
	ctx->mmap_ptr = _data;
	close(fd);
	return 0;
}
