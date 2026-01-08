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

    int mmap_read(const std::string& filename) {
        struct stat fileStatus;

        // open the file in read-only mode
        int fd = open(filename.c_str(), O_RDONLY);
        if (fd == -1) {
            std::cerr << "Error opening file: " << filename << std::endl;
            return 1;
        }

        // get file size using fstat
        if (fstat(fd, &fileStatus) == -1) {
            std::cerr << "Error getting file status" << std::endl;
            close(fd);
            return 1;
        }
        
        size_t fsize = fileStatus.st_size;

        // print the size 
        std::cout << "File: " << filename << " size is " << fsize << std::endl;

        // perform mapping operation
        void *addr = mmap(NULL, fsize, PROT_READ, MAP_SHARED, fd, 0);
        if (addr == MAP_FAILED) {
            std::cerr << "Error mapping file" << std::endl;
            close(fd);
            return 1;
        }
        
        // print address content
        std::cout << (char*)addr << std::endl;

        // unmap and close
        munmap(addr, fsize);
        close(fd);
        
        return 0;
    }

    int mmap_update(const std::string& filename, const std::string& message) {
        struct stat fileStatus;

        // initialize length of message
        size_t length = message.length() + 1;

        // declare fd (file descriptor variable)
        int fd = open(filename.c_str(), O_RDWR, PERM);
        if (fd == -1) {
            std::cerr << "Error opening file: " << filename << std::endl;
            return 1;
        }

        // use fstat to get size of the file
        if (fstat(fd, &fileStatus) == -1) {
            std::cerr << "Error getting file status" << std::endl;
            close(fd);
            return 1;
        }
        
        size_t fsize = fileStatus.st_size;
    
        // print size of file
        std::cout << "File: " << filename << " size is " << length << ":" << fsize << std::endl;

        // mmap operation with proper flags
        void *addr = mmap(NULL, fsize, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
        if (addr == MAP_FAILED) {
            std::cerr << "Error mapping file" << std::endl;
            close(fd);
            return 1;
        }

        // print original content
        std::cout << "Original: " << (char*)addr << std::endl;

        // memcpy new message
        memcpy(addr, message.c_str(), message.length() + 1);
        
        // print after copy
        std::cout << "Updated: " << (char*)addr << std::endl;

        // sync changes back to disk
        msync(addr, fsize, MS_SYNC);

        // unmap and close
        munmap(addr, fsize);
        close(fd);

        return 0;
    }

    // Implementation of mmapWriter methods
    int mmapWriter::mmap_create(const std::string& filename, const std::string& message) {
        return ::mmapwriter::mmap_create(filename, message);
    }

    int mmapWriter::mmap_read(const std::string& filename) {
        return ::mmapwriter::mmap_read(filename);
    }

    int mmapWriter::mmap_update(const std::string& filename, const std::string& message) {
        return ::mmapwriter::mmap_update(filename, message);
    }
}
