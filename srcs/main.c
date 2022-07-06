#include "wpacker.h"

void	print_usage()
{
	ft_printf(1, "Usage: ./woody_woodpacker <program>\n");
	exit(127);
}

int main(int argc, char **argv)
{
	FILE			*ptr;
	unsigned char	buffer[1024];

	if (argc != 2)
		print_usage();
	ptr = fopen(argv[1], "rb");
	fread(buffer, sizeof(buffer), 1, ptr);
	for(int i = 0; i<10; i++)
		printf("%x \n", buffer[i]); // prints a series of bytes
}
