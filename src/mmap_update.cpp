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
        std::cout << "Usage: mmap_update <file-name> <Message" << std::endl;
    }

    // initialize length of arguments

    // declare fd (file descriptor variable using args, O_RDWR, and the linux permission)

    // use fstat to get size of the file
    fstat(fd, &fileStatus);
    // then call filestatus.st_size in fsize variable declaration
    
    // print size of file args

    // mmap operation with proper flags into addr variable

    // print read addre vsraible

    // memcpy 

    // print after copy

    // sync

    // unmap

    // close

    // return succes



}