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

#include "../include/spsc_queue1.hpp"
#include "../include/mmap_writer.hpp"
#include <iostream>
#include <string>
#include <format>
#include <chrono>
#include <thread>


// modularize into different functions first

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
struct LogInfo {
    LogLevel label;
    std::chrono::system_clock::time_point timestamp;
    std::string level;
    std::string message;
    std::string formatted_message;
    std::string filename;
    int line;
    std::string function;
    unsigned long long thread_id;
};

// Step comes after creating log message struct
// Within here, create log messsafe function, use variadic template for the function
// as they allow for an arbitrary amount of arguments
// use struct as user defined type to create this create log function
template <typename...Args>
// find out what fmt here is
LogInfo createlogmessage(const std::string& level, std::format_string<Args...> fmt, Args&&... args) {
    // Figure out how to change this for my implementation
    // creation fo msg variable using LogInfo struct is important for other variables 
    LogInfo msg;
    msg.timestamp = std::chrono::system_clock::now();
    msg.level = level;
    msg.formatted_message = std::format(fmt, std::forward<Args>(args)...);
    return msg;
}

// problem that i need to fix: createlogmessage has a declaration of msg variable using the 
// log ingo struct
// Create logmessage struct (done)

// format the final string (also likely done?)

int main(int argc, char* argv[]) {

    // call the createlogmessage function, and an example log insertion. 
    // Double check if this struct is converted into a string from previous
    // function, and also fix the arguments in this example creation, so that it is
    // properly in tune with function declaration above
    LogInfo my_log = createlogmessage("INFO", "User {} logged in from IP {}", "Ananth Junutula", "192.168.1.1");

    // Queue the log message (call spscqueue function)
    highLogger::SPSCQueue<LogInfo> queue(100);

    // 1. Producer and Consumer Thread Logic

    // producer thread logic
    queue.emplace(my_log);

    // 1a. consumer side that drains the queue: queue.front() then move to mmap operations then pop

    LogInfo* queuedMsg = queue.front();

    // 1b. mmap functions need to accept LogInfo data
    // Then need to convert LogInfo to string format for disk writing, and to be
    // able to send it to the mmap operations
    // 2. then actually perform file writing through memory mmapping
    // that was builtz

    // Remove argc check - not needed for demo 

    
    // pop from the queue
    while (!queue.empty()) {
        queue.pop();
    }

    // 3. Error Handling
    // cases to handle:
    // What happens when queue is full
    // what happens when disk write fails, what causes that
    // basic error recovery strats and implement that


    // 4. configuration system
    // log level filtering (only write ERROR)
    // file rotation policies
    // output file paths

    // 5. performance optimizations
    // SIMD parser implementation
    // memory pool allocation
    // batch processing multiple messages, that actual "concurrent" processes

    // Create mmap_writer instance and write log
    mmapwriter::mmapWriter writer;
    writer.mmap_create("test.log", my_log.formatted_message);
    writer.mmap_read("test.log");
    
    return 0;
}
