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
#include <iostream>
#include <sys/mman.h> // mmap and unmmap operations
#include <fcntl.h> // open
#include <unistd.h> // close
#include <sys/stat.h> // interacting with files

// permit for linux/unix
#define PERM 0644

/*
// declare file that will be worked on as a char variable
    
    // ensure file has desired size

    // map the file into memory using the mmap operation

    // access and modify data through the memory mapped region

    // write initial data

    // modify data

    // unmap the memroy region

    // close file descriptor

    // verify chnages by reading the file

    // cleanup: remove the file

Goal of this modular program will be how to create, read, update, read, writer, mmap
to files

mmap allows a progrmam to directly acces file data as if
it were part of the programs memory

can be split into mmap_create.cpp, mmap_read.cpp, mmap_update.cpp
using mmap to create files, using mmap to read files, using mmap to update files
*/

int main(int argc, char *argv[]) {
    // if statement to open the file

    // declare size of arguments

    // open file and get the fd (file descriptor)

    // print the size of the file

    // set the file size

    // mapping

    // copy length of message into memory using mcpy

    // synchronize memory to file using msync

    // unmap

    // close the file (fd) variable
}