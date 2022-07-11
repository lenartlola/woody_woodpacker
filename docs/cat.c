#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char **argv) {
    if (argc != 2) {
        printf("Error\n");
        printf("Usage: %s <a text file to read>\n", argv[0]);
        exit(127);
    }

    int fd = open(argv[1], O_RDONLY);
    if (fd == -1) {
        printf("could not open file\n");
        exit(1127);
    }

    const size_t buffer_size = 16;
    char *buffer = malloc(buffer_size);

    while (true) {
        ssize_t size = read(fd, buffer, buffer_size);

        if (size == -1) {
            printf("an error happened while reading the file");
            exit(127);
        }
        if (size == 0) {
            break;
        }
        write(STDOUT_FILENO, buffer, size);
    }
    
    write(STDOUT_FILENO, "\n", 1);
    return (0);
}
