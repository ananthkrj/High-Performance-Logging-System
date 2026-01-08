#include "../include/mmap_writer.hpp"
#include <iostream>
#include <sys/mman.h> // for mmap and unmap operations
#include <sys/stat.h> // for struct stat, and file status functions
#include <fcntl.h> // to open file 
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // to close files
#include <cstring>

// permit for linux/unix
#define PERM 0644

namespace mmapwriter {
class mmapWriter {
public:
    int mmap_create(const std::string& filename, const std::string& message) {
        // declare the overall size of the message in a fsize variable
        size_t fsize = message.length() + 1;

        // open file and get the fd (file descriptor)
        // FLAGS will setup the file before mapping it to memory
        // these flags will create file if not already, to be opened
        // for reading and writing, and can be truncated to 0 bytes
        int fd = open(filename.c_str(), O_CREAT | O_RDWR | O_TRUNC, PERM);
        if (fd == -1) {
            std::cerr << "Error opening file: " << filename << std::endl;
            return 1;
        }
        
        // print the size of the file
        std::cout << "File: " << filename << " size is " << fsize << std::endl;

        // set the file size using lseek, which repositions to 
        // read/write file offset, just setting offset to 0
        lseek(fd, fsize-1, SEEK_SET);
        write(fd, "\n", 1);
    
        // mapping, using more flags and declare addr as a void pointer
        // store this mmapping in memory variable addr
        void *addr = mmap(NULL, fsize, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
        if (addr == MAP_FAILED) {
            std::cerr << "Error mapping file" << std::endl;
            close(fd);
            return 1;
        }
        
        // copy length of message into memory using memcpy
        memcpy(addr, message.c_str(), message.length());
        // synchronize memory to file using msync
        msync(addr, fsize, MS_SYNC);
        // unmap, just pass the memory var and size
        munmap(addr, fsize);
        // close the file (fd) variable
        close(fd);
        
        return 0;
    }

    int mmap_read(int argc, char* argv[]) {
        struct stat fileStatus;

        // can only have one arguemnt, being the filename
        // return success if this happens sucessfully
        if (argc != 2) {
            std::cout << "Usage: mmap_read <file-name>" << std::endl;
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
    }

    int mmap_update(int argc, char* argv[]) {
        if (argc != 3) {
            std::cout << "Usage: mmap_update <file-name> <Message>" << std::endl;
        }

        struct stat fileStatus;

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

        return EXIT_SUCCESS;
    }

    // place holder of what should go in the logger file
    int main(int argc, char* argv[]) {
        std::string command = argv[1];

        if (argc != 4) {
            std::cout << "Usage : create mmap_create <file-name> <Message>" << std::endl;
            return EXIT_SUCCESS;
        } 
        else if (command == "read") {
            std::cout << "Usage : read mmap_read <file-name>" << std::endl;
            return EXIT_SUCCESS;
        } 
        else if (command == "update") {
            std::cout << "Usage : update mmap_update <file-name> <Message" << std::endl;
            return EXIT_SUCCESS;
        } else {
            std::cout << "Only available commands are: create, read, update" << std::endl;
            std::cout << "Enter a valid command: " << command << std::endl;
            return 1;
        }
        return 0;
    }
};
}
