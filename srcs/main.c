#include "wpacker.h"

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
