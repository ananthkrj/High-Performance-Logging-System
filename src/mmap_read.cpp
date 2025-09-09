/*

*/
#include <iostream>
#include <sys/mman.h> // for man an unmap operations
#include <sys/stat.h> // for struct stat, and file status functions
// fogire 
#include <fcntl.h> // to open file 
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // to close files

// struct stat is used to retrieve info on a file, notably its size

int main(int argc, char *argv[]) {
    struct stat fileStatus;

    // can only have one arguemnt, being the filename
    // return success if this happens sucessfully
    if (argc != 2) {
        std::cout << "Usage: mmap_read <file-name> " << std::endl;
        return 1;
    }

    // open the file, so intiailzie the fd variable with
    // the arguments and rd only mode O_RDONLY
    int fd = open(argv[1], O_RDONLY);

    // get file size using fstat, and fd, pass fileStatus by address
    fstat(fd, &fileStatus);
    // can get size of file using file status variable created with
    size_t fsize = fileStatus.st_size;

    // print the size 
    std::cout << "File: " << argv[1] << " size is " << fsize << std::endl;

    // perform mapping operstion in void pointer named addr
    // the only flags we need for reading operations
    // should be PROT_READ so that pages can be read, and MAP_SHARED
    // so that updates to the mapping can viewed to other processes
    // pass in memory address, size, flags, fd (file descriptor), offset
    void *addr = mmap(NULL, fsize, PROT_READ, MAP_SHARED, fd, 0);
    // print address to test, type cast address
    std::cout << (char*)addr << std::endl;

    // unmap, no need to copy memory or sync any memory
    munmap(addr, fsize);

    // close 
    close(fd);

    return EXIT_SUCCESS;
}