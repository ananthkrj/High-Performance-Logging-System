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

#include <include/rigtorps_spsc_queue.hpp>
#include <src/mmap_writer.cpp>
#include <iostream>
#include <string>
#include <format>



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
    // use chrono type for timestamp
    std::string level;
    std::string message;
    std::string filename;
    int line;
    std::string function;
    // why does the thread_id need to be unsigned and a long long:
    // because it may be an extremely long number
    unsigned long long thread_id;
};

// Step comes after creating log message struct
// Within here, create log messsafe function, use variadic template for the function
// as they allow for an arbitrary amount of arguments
// use struct as user defined type to create this create log function
template <typename...Args>
// find out what fmt here is
LogInfo createlogmessage(const std::string& level, std::format_string<Args...> fmt, Args&&... args) {
    LogInfo msg;
    /*
    Figure out how to change this for my implementation
    // creation fo msg variable using LogInfo struct is important for other variables 
    LogInfo msg;
    msg.timestamp = std::chrono::system_clock::now();
    msg.level = level;
    msg.formatted_message = std::format(fmt, std::forward<Args>(args)...);
    return msg;

    in logging system goal creation of a log should look like this:
    LogInfo my_log = createlogmessage("INFO", "User {} logged in from IP {}", "Alice", "192.168.1.1");
    */
}

int main(int argc, char* argv[]) {
    // 1. parse format string
    // making progress toward this above

    // 2. Create logmessage struct (done)

    
    // 3. format the final string (also likely done?)

    // 4. Queue the log message (call spscqueue function)
    highLogger::SPSCQueue<int> queue();

    // find way to define createlog message here, likely need to call function
    LogInfo msg = queue.emplace();
    LogInfo msg = queue.push();

    // pseudo code, obviously write a real condition which checks if the queue has
    // element in it (msg or not)
    while (queue_has_data) {
        LogInfo msg = queue.pop();
    }

    // 5. consumer side, pop from queue, mmap writer writes to the disk
    // just mini part, need to alter
    // i know i am passing in the msg as an argument, so need to make changers
    // to mmap_writer file
    // also find out what msg.formatted_string does
    mmapwriter::mmap_create(1, msg.formatted_string);
    mmapwriter::mmap_read(1, msg.formatted_string);
}