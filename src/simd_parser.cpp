// AVX-512  Vectorized string parsing for extracting
// timestamps, log levels, and structured fields from raw log lines

// Why important: Parallel processing of multiple log entries simultaneosly

/*
The simd parser directly works with the cpu, as it handles 
the CPU intensive string operations

simd parser is very important for the optimization portiion
of this logging system

it allows the logging system to process 4 - 16 characters of a log
simultaneously instead of 1 character at a time. 

Making it critical for properly logging millions of messages 
quickly

string operations are also the bottleneck usually in logging systems\

implementation approach:
1. simple operations (comparing 16 characters at once)
2. build up to string processing patterns (so char -> string)
3. data alignment and memory access patterns
*/