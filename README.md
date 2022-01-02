# get_next_line
Returns the next read line of a file identified by a file descriptor.
It supports reading many file descriptors.

## Installation
```console
git clone https://github.com/chriss1245/get_next_line.git
```
```console
make -C get_next_line
```

## Usage
*Inside your files*
```c 
#include "get_next_line/inc/ft_get_next_line.h"
````
```c 
char *s = get_next_line(fd);
````

*When compiling*
```console
gcc your_files.c get_next_line/libgnl.a
``` 

## How it works
It uses a static array of strings called buffer of MAX_FD len. When a file descriptor is passed, it mallocates memory (if not done already) of BUFFER_SIZE + 1. When the file is completely read, it frees the memomory of the string corresponding to the file descriptor.

The file is read in steps of BUFFER_SIZE characters until the EOF or the line break are read. It returns a string until the line break or the EOF.

The extra read characters are stored in the buffer[fd] string.

## Headerfile
There are primitive functions required by get_next_line. These funcitons are available an can be used importing the ``get_next_line.h``. However these functions are not that well structured. It is possible that we exclude them from the main headerfile.

