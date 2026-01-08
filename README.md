# High-Performance-Logging-System
A data ingestion and storage engine that can handle millions of log entries per second.

# core components
- A SPSC queue is a single producer single consumer queue implementation built off atomic operations 
- SPSC queue is needed here as it is key to transfer logs from application thread (producer)
to dedicated logging thread (consumer)

# Overall Architecture:
Data Flow:
- Producer: Application -> Logger -> SIMD Parser -> SPSCQueue
- Consumer: SPSCQueue -> batch processing -> mmap_writer -> disk

Goal of each core file:
- spsc_queue: lock free consumer/producer buffer
- simd_parser: Vectorized string operations and formatting
- mmap_writer: memory mspped file i/o with rotation
- logger: orchestrates entire pipeline

**What I need Claude Code to help me with**
Please read this README.md file first and then go through the files of code i have in this project. I want you to let me know how close I am to getting a working logger based on the existing code in this project, and then 
how to actually get that working logger to compile without errors and to actually test it. Obviously i beleive I have errors in my existing code files so we need to fix those as well. All the code I have right now was written by myself, now the goal is to get to an error free end product with your help as efficiently as possible.
