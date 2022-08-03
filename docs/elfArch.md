# The anatomy of ELF

readelf is a program that recognizes and displays the ELF metadata
of a binary file, be it an object file or an executable binary. ELF, or Executable
and Linkable Format, is the content at the very beginning of an executable
to provide an operating system necessary information to load into main
memory and run the executable.

ELF can be thought of similar to the
table of contents of a book. In a book, a table of contents list the page
numbers of the main sections, subsections, sometimes even figures and
tables for easy lookup. Similarly, ELF lists various sections used for code
and data, and the memory addresses of each symbol along with other information.

An ELF binary is composed of:

* ELF header: the very first section of an executable that describes ELF header
  the file’s organization.
* Program header table: an array of fixed-size structures that describes segments of an executable.
* Section header table: an array of fixed-size structures that describes sections of an executable.
* Segments and sections: The main content of an ELF binary, which are the code and data, divided into chunks of different purpose.

A segment is a composition of zero or more sections and is directly loaded
by an operating system at runtime.

A section is a block of binary that is either:
- actual program code and data that is available in memory when a program runs.
- metadata about other sections used only in the linking process, and disappear from the final executable.    

Linker uses sections to build segments.
