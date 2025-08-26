// memory mapped file I/O  with pre-allocated buffers, sequential writes, 
// and atomic file rotation

// why important: Direct memory to disk, bypasses kernel buffering overhead.
// 10 - 100x times faster than standard file io for write heavy workloads
// like logging

// goals: find out what a mmap writeer even does 
// (likely need to write heavy workloads)
