#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char **argv) {
    int fd;
    struct stat buf;

    if (argc != 2) {
        printf("Error\n");
        printf("Usage: %s <a text file to read>\n", argv[0]);
        exit(127);
    }

    fd = open(argv[1], O_RDONLY);

    if (fd == -1) {
        printf("could not open file\n");
        exit(127);
    }

    const size_t buffer_size = 16;
    if (fstat(fd, &buf) != 0)
    {
        printf("Failed to stat a file");
        exit(127);
    }
    
    char *buffer = malloc(buf.st_size);

    ssize_t size = read(fd, buffer, buf.st_size);

    if (size == -1) {
        printf("an error happened while reading the file");
        exit(127);
    }
    
    write(STDOUT_FILENO, buffer, size);
    
    
    write(STDOUT_FILENO, "\n", 1);
	free(buffer);
    return (0);
}
