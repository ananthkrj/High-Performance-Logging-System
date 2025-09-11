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
    // need a struct to define the levels of a log (message severity)
    // use enum to create new data type with my own parameters
    // that will makeup one of single log entry parmeters
    enum class LogLevel {
        TRACE,
        WARN,
        ERROR,
        CRITICAL
    };

    // and another struct to hold the information for a single log entry
    // create logentry datastructure using struct
    // level, timestamp, message, filename, line, function, and 
    // thread_id will go into this struct
    // struct will allow me to bundle multiple variables into a single 
    // so it is perfect here
    struct logs {
        LogLevel label;
        // use chrono type for timestamp
        std::string message;
        std::string filename;
        int line;
        std::string function;
        // why does the thread_id need to be unsigned and a long long:
        // because it may be an extremely long number
        unsigned long long thread_id;
    };

    // find out if i need list initalization or constructor after
    // here to actually utilize the test creation of a log

    // find out how do i actually test inputting a log properly here
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