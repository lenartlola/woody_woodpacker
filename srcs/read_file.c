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

int
init_struct(char *file, char **data)
{
	//char*	*data;
	int		fd;
	ssize_t len;

	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		ft_printf(2, "Failed t open file %s, REASON: %s\n", file, strerror(errno));
		return -1;
	}
	
	len = lseek(fd, (size_t)0, SEEK_END);
	if (len == -1)
	{
		ft_printf(2, "Error happened in lseek, REASON: %s\n", strerror(errno));
		close(fd);
		return -1;
	}
	
    *data = mmap(NULL, len, PROT_READ | PROT_WRITE, MAP_PRIVATE, fd, (size_t)0);
	if (*data == MAP_FAILED)
	{
		ft_printf(2, "Error happened while mapping memory, REASON: %s\n", strerror(errno));
		close(fd);
		return -1;
	}

	if (elf_sanitizer(*data) != 0)
	{
		ft_printf(2, "[-] Error: invalid ELF file\n");
		close(fd);

		if (munmap(*data, len) == -1)
			ft_printf(2, "[-] Error happened while unmaping memory, REASON: %s", strerror(errno));
		return -1;	
	}
	
	//ctx->mmap_ptr = *data;
	//if (*data[4] == 2) {
	//	get_x64_86_segments(*data, ctx);
	//}
	//else if (*data[4] == 1) {
	//	ft_printf(2, "[!] TODO 32 bit arch\n");
	//	return 1;
	//}
	close(fd);
	return len;
}
