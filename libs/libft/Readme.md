# libft.h

## A collections of standard C library functions with some additional ones.


The aim of this project is to re-create some standard C library functions, the functions created in Libft will become the basic building blocks of later projects that we are going to create in the later of the program.
Using C standard library at 42 is strictly forbidden, the only functions we're allowed to use are the functions created by ourselves using few basic standard functions like `write(), malloc(), free()`.

Every type of errors "Segmentation fault, buss error, memory overflow, memory overlapping, etc" should be handled carefully.

## Build

Clone this repository.
```sh
https://github.com/1mthe0wl/libft
```

cd into the libft directory.

```sh
cd libft
```

Make

```sh
make
```

delete all the *.o files.
```sh
make clean
```

Delete all the *.0 files plus libft.a
```sh
make fclean
```

Remake everything.
```sh
make re
```

## Manual
| functions | description |
| ------ | ------ |
| ft_atoi | converts ASCII string to integer. |
| ft_bzero | Writes zeroes to byte string. |
| ft_calloc | Contiguously allocates size bytes of memory and returns a pointer to the allocated memory. |
| ft_isalpha | Checks if a character is whether alphabetic or not. |
| ft_isdigit | checks if a character is a digit or not. |
| ft_isalnum | Checks if a character isalpha or isdigit or non-alnum. |
| ft_isascii | Cheks whether a character is ascii or not. |
| ft_isprint | Checks if a character is printable or not. |
| ft_itoa | Recives an integer and converts it to a string with allocating enough space for it. |
| ft_memchr | Scans memory for string. |
| ft_memcmp | Compares two memory areas of string. |
| ft_memcpy | Copies an area of memory to another. |
| ft_memmove | Moves an area of memory to another. |
| ft_memset | Writes n area of memory with a byte value. |
| ft_putchar_fd | Writes a character to a file descriptor. |
| ft_putendl_fd | Writes a string to a file descriptor, followed by a new line. |
| ft_putnbr_fd | Writes a number to a file descriptor. |
| ft_putstr_fd | Writes a string to a file descriptor. |
| ft_split | Split a string using a given character as a second parameter. |
| ft_strchr | Locates character in string. |
| ft_strdup | Duplicates a string. |
| ft_striteri | Applies a function to eacg character of a string. |
| ft_strjoin | Concatinates two string. |
| ft_strlcat | Concatinates two string to a bounded size. |
| ft_strlcpy | Copies a string to anothere to a bounded size. |
| ft_strlen | Returns length of a given string. |
| ft_strmapi | Applies a function to each character of a given string. |
| ft_strncmp | Compares two string to n character. |
| ft_strnstr | Locates a substring in a string. |
| ft_strrchr | Locates character in string. |
| ft_strtrim | Trims the beginning and the end of a string if they match the given chars. |
| ft_substr | Returns a substring in a given string from a given index to a given length. |
| ft_tolower | Convert char to lowercase. |
| ft_toupper | Convert char to uppercase. |

## Functions without standard manual

- ft_substr : 

        char *ft_substr(char const *s, unsigned int start,size_t len);

        1.  The string from which to create the substring.
        2.  The start index of the substring in the string’s’.
        3.  The maximum length of the substring.

- ft_strjoin : 

        char *ft_strjoin(char const *s1, char const *s2);

        1.  The prefix string.
        2.  The suffix string.

- ft_strtrim : 

        char *ft_strtrim(char const *s1, char const *set);

        1.  The string to be trimmed.
        2.  The reference set of characters to trim.

- ft_split : 

        char **ft_split(char const *s, char c);

        1.  The string to be split.
        2.  The delimiter character.
       
- ft_itoa : 

        char *ft_itoa(int n);

- ft_strmapi : 

        char *ft_strmapi(char const *s, char (*f)(unsignedint, char));
        
        1.  The string on which to iterate.
        2.  The function to apply to each character.

- ft_striteri : 

        void ft_striteri(char *s, void (*f)(unsigned int,char*));
        
        1.  The string on which to iterate.
        2.  The function to apply to each character.

- ft_putchar_fd : 

        void ft_putchar_fd(char c, int fd);
        
        1.  The character to output.
        2.  The file descriptor on which to write.
        

- ft_putstr_fd : 

        void ft_putstr_fd(char *s, int fd);
        
        1.  The string to output.
        2.  The file descriptor on which to write.

- ft_putendl_fd : 

        void ft_putendl_fd(char *s, int fd);
        
        1.  The string to output.
        2.  The file descriptor on which to write.
        
- ft_putnbr_fd : 

        void ft_putnbr_fd(int n, int fd);
        
        1.  The integer to output.
        2.  The file descriptor on which to write.
        
### What is a file descriptor?
[RTFWikipedia](https://en.wikipedia.org/wiki/File_descriptor)

## get_next_line
`char *get_next_line(int fd)`
Calling the function in a loop will read line by line on the file descriptor until the EOF.
It returns the line that has been read.


## ft_printf
`int ft_printf(const char *format, ...)`
- `%c` print a single character.
- `%s` print a string of characters.
- `%p` print the pointer in hexadecimal.
- `%d` print a decimal number.
- `%i` print an integer in base 10.
- `%u` print an unsigned decimal (base 10) number
- `%x` print a number in hexadecimal (base 16) with lowercase.
- `%X` print a number in hexadecimal (base 16) with uppercase.
- `%%` print a percent sign.
- `-` left-justify within the given field width; Right justification is the default.
- `0` left-pads the number with zeroes (0) instead of spaces when padding is specified.
- `.` the precision in not specified in the format string, but as an additional integer value argument preceding the argument that has to be formated.



**Free Software, Hell Yeah!**

[![forthebadge](https://forthebadge.com/images/badges/made-with-c.svg)](https://forthebadge.com) [![forthebadge](https://forthebadge.com/images/badges/contains-tasty-spaghetti-code.svg)](https://forthebadge.com)
