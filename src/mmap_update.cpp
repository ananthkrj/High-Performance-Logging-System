/*
mmap operations for updating file, actually writing to
file
*/
#include <iostream>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define PERM 0644


int main(int argc, char *argv[]) {
    struct stat fileStatus;

    // need two argumentsm so args cant be 3
    if (argc != 3) {
        std::cout << "Usage: mmap_update <file-name> <Message>" << std::endl;
    }

    // initialize length of arguments
    size_t length = strlen(argv[2]) + 1;

    // declare fd (file descriptor variable using args, O_RDWR, and the linux permission)
    int fd = open(argv[1], O_RDWR, PERM);

    // use fstat to get size of the file
    fstat(fd, &fileStatus);
    // then call filestatus.st_size in fsize variable declaration
    size_t fsize = fileStatus.st_size;
    
    // print size of file args
    std::cout << "File : " << argv[1] << " size is" << length << ":" << fsize << std::endl;

    // mmap operation with proper flags into addr variable 
    // need to pass memory address (let compiler decide, size, prot read, and 
    // write flags, map shared flag fd, then the offsert which is 0)
    void *addr = mmap(addr, fsize, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

    // print read addre vsraible
    std::cout << (char*)addr << std::endl;

    // memcpy 
    // copy address and arguments, then pass in length of the arguments
    memcpy(addr, argv[2], strlen(argv[2]) + 1);
    // print after copy, print the type casted addr
    std::cout << (char*)addr << std::endl;

    // sync addr fisze, (writing changes back to the disk)
    msync(addr, fsize, MS_SYNC);

    // unmap
    munmap(addr, fsize);

    // close
    close(fd);

    // return succes
    return EXIT_SUCCESS;
}