
//#include "wpacker.h"

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>


/**
 * ELF: Executable and Linkable Format
 * This is a simple program to read the ELF file header,
 * The offsets can be found on wikipedia.
 * https://en.wikipedia.org/wiki/Executable_and_Linkable_Format
 * @lseek shall change the pointer on the fd onto a specific offset.
 */

void	print_usage()
{
	printf("Usage: ./woody_woodpacker <program>\n");
	exit(127);
}

int main(int argc, char **argv)
{
	int	ffd;
	char	buffer[1024];

	if (argc != 2)
		print_usage();
	ffd = open(argv[1], O_RDONLY);
	if (ffd == -1)
	{
		printf("Error: couldn't open %s\n", argv[1]);
		exit(127);
	}
	read(ffd, buffer, 4);
	buffer[4] = '\0';
	int i = 0;
	printf("The file signature:\n");
	printf("\t");
	while(buffer[i])
	{
		printf("0x%x ", buffer[i]);
		i++;
	}
	printf("\n");
	lseek(ffd, 0x4, SEEK_SET);
	read(ffd, buffer, 1);
	printf("System arch:\n \t0x%x\n", buffer[0]);
	lseek(ffd, 0x07, SEEK_SET);
	read(ffd, buffer, 1);
	lseek(ffd, 0x12, SEEK_SET);
	read(ffd, buffer, 2);
	printf("Instruction set arch\n");
	i = 0;
	printf("\t0x%x\n", buffer[i]);

}
