// main api that coordinates the queue, parser, and writer. Handlers configuration,
// error recovery, and thread management

// Why important: it is the system orchestrator

/*
core goal to follow for the main orchestration file:
Make it work, make it concurrent, then make it fast

Overall plan and build order:
1. Message format (define the data structures and kind of data the logging system can handle)
2. Basic pipeline integration (core flow working)
3. threads (concurrent, multithreaded processes)
4. condfiguration and control (make system configurable)
5. simd integration points (also start simd parser file here)

of course error handlign throughout

build progression from simple to advanced
1. single threadd version: log() -> format -> queue -> mmap writer

q's: what will represent in log()? i still need to solve bottleneck
where logs are actually being formatted and sent to the queue

2. add consumer thread: separate producer from consumer
3. add thread management: proper startup and shutdown
4. add configuration: make logging system flexibly
5. add optimization (SIMD)
*/

#include <iostream>

// modularize into different functions first
void messageFormat() {

}

void pipeline() {

}

// likely need to add concurrency to pipeline function itself
void threading() {

}

void configuration() {

}

int main() {
    // will call simd here
}