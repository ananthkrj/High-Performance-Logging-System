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
    // cannot have 3 arguments
    if (argc != 3) {
        std::cout << "Usage : mmap_create <file-name> <Message>" << std::endl;
        return 1;
    }

    // declare the overall size of the arguments in a fsize variable
    size_t fsize = strlen(argv[2]) + 1;

    // open file and get the fd (file descriptor)
    // FLAGS will setup the file before mapping it to memory
    // these flafs will create file if not already, to be opened
    // for reading and wiring, and can be truncated to 0 bytes, and only 
    // done with permission
    int fd = open(argv[2], O_CREAT | O_RDWR | O_TRUNC, PERM);
    // print the size of the file
    std::cout << "File: " << argv[1] << " size is " << fsize << std::endl;

    // set the file size using lseek, which repositions to 
    // read/write file offset, just setting offset to 0
    lseek(fd, fsize-1, SEEK_SET);
    write(fd, "\n", 1);
    
    // mapping, using more flags and declare addr as a vpid pointer
    // store this mmapping in memory variable addr
    void *addr = mmap(NULL, fsize, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    // copy length of message into memory using mcpy
    memcpy(addr, argv[2], strlen(argv[2]));
    // synchronize memory to file using msync
    msync(addr, fsize, MS_SYNC);
    // unmap, just pass the memory var and size
    munmap(addr, fsize);
    // close the file (fd) variable
    close(fd);

    // need to test
    return EXIT_SUCCESS;
}