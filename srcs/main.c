#include "wpacker.h"

void	print_usage()
{
	ft_printf(1, "Usage: ./woody_woodpacker <program>\n");
	exit(127);
}

int main(int argc, char **argv)
{
	int	ffd;
	char	buffer[1024];

	if (argc != 2)
		print_usage();
	ffd = open(argv[1], O_RDONLY);
	//lseek(ffd, 0x4, SEEK_SET);
	read(ffd, buffer, 4);
	buffer[4] = '\0';
	int i = 0;
	while(buffer[i])
	{
		printf("0x%x ", buffer[i]);
		i++;
	}
}
