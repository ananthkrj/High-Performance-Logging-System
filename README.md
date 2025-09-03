# High-Performance-Logging-System
A data ingestion and storage engine that can handle millions of log entries per second.

# What is a logging system, why make it "high performance"



# core components
a SPSC queue is a single producer single consumer queue implementation built off atomic operations 
- SPSC queue is needed here as it is key to transfer logs from application thread (producer)
to dedicated logging thread (consumer)
- key concept to understand: Thread to thread communication and using atomics to achieve this
- readIndex and writeIndex are atomic counters used by two separate threads to coordinate access to a shared bugger

mmap_writer

sim_parser

logger