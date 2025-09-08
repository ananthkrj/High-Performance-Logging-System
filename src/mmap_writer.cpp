/*
Start with a basic mmap example

Where I map a file, write some bytes, and then unmap

core systems concepts:
1. mmap system calls
2. file I/O system calls

core cpp concepts:
1. RAII
2. error handling
3. templates
4. move semantics

How to turn this concept into code:

need to include mman.h for mmap
and specific libraries for opening
and closing files
*/
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>

namespace writer {

class mmap_writer {
    // declare file that will be worked on as a char variable

    // ensure file has desired size

    // map the file into memory using the mmap operation

    // access and modify data through the memory mapped region

    // write initial data

    // modify data

    // unmpa the memroy region

    // close file descriptor

    // verify chnages by reading the file

    // cleanup: remove the file
};
}