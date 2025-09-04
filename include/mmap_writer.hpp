// memory mapped file I/O  with pre-allocated buffers, sequential writes, 
// and atomic file rotation

// why important: Direct memory to disk, bypasses kernel buffering overhead.
// 10 - 100x times faster than standard file io for write heavy workloads
// like logging

// goals: find out what a mmap writeer even does 
// (likely need to write heavy workloads)

/*
key topics:
1. core mmap concepts
   - mmap() system calls anf flags
   - numap() for cleanup
   - file descriptor management for open() and close()

2. file management
   - ftruncate() or fallocate()
   - file rotation logic
   - atomic file operations for safe rotation

3. Memory management
    - buffer boundary checking
    - page eligment considerations
    - handling write positions and offsets

4. Error handling
    - mmap() failure cases
    - permission issues
    - disk space exhaustion


Process to go from concepts to code:
1.start with basic mmap example
    - map a file, write some bytes, unmap

2. add pre-allocation
    - create files of fixed size upfront

3. add sequential writing
    - track current write position

4. add rotation logic
    - create new files when current is full

5. add atomic operations
    - ensure thread safe rotation

header: estimated 60 - 80 lines of code
*/

/*
1. Start with a basic mmap Example
Need to map a file, write some bytes to the file, then unmap
*/
namespace writer {

class mmap_writer {

};
}