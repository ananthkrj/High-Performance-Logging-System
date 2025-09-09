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

    // get file size using fstat, and fd

    // print the size 

    // perform mapping operstion in void pointer named addr
    // flkas will be prot read and map shared

    // print address to test

    // unmap

    // close 
}