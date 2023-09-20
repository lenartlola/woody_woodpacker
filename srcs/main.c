#include "wpacker.h"

/*
 * This shellcode will write ....WOODY.... followed by a newline to the stdout.
 * For more information look at write.asm file
 */
//char shellcode[] = "\xbf\x00\x00\x00\x00\x48\x8d\x35\x13\x00\x00\x00\xba\x0e\x00\x00\x00\xb8\x01\x00\x00\x00\x0f\x05\xb8\x3c\x00\x00\x00\x0f\x05\x2e\x2e\x2e\x2e\x57\x4f\x4f\x44\x59\x2e\x2e\x2e\x2e\x0a";

int main(int argc, char **argv)
{
	if (argc != 2)
	{
		ft_printf(1, "Usage: ./woody_woodpacker <program>\n");
		return 1;
	}

	if (pack_elf(argv[1]))
		return 1;
	return 0;
}
