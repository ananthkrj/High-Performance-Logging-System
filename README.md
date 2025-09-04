# High-Performance-Logging-System
A data ingestion and storage engine that can handle millions of log entries per second.

# What is a logging system, why make it "high performance"



# core components
- A SPSC queue is a single producer single consumer queue implementation built off atomic operations 
- SPSC queue is needed here as it is key to transfer logs from application thread (producer)
to dedicated logging thread (consumer)
- key concept to understand: Thread to thread communication and using atomics to achieve this
- readIndex and writeIndex are atomic counters used by two separate threads to coordinate access to a shared bugger

# Overall Architecture:
Data Flow:
- Producer: Application -> Logger -> SIMD Parser -> SPSCQueue
- Consumer: SPSCQueue -> batch processing -> mmap_writer -> disk

Goal of each core file:
- spsc_queue: lock free consumer/producer buffer
- simd_parser: Vectorized string operations and formatting
- mmap_writer: memory mspped file i/o with rotation
- logger: orchestrates entire pipeline

**Goal for sep 4th**
1. get to working on mmap_writer. try to have bones implementation done and test out member funcs