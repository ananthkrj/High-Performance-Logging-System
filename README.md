# High-Performance-Logging-System
A data ingestion and storage engine that can handle millions of log entries per second.

## Core Components

### 1. **SPSC Queue** (`include/spsc_queue1.hpp`)
- **Purpose**: Lock-free single-producer, single-consumer queue for thread-safe log message passing
- **Implementation**: Built on atomic operations for maximum performance
- **Role**: Transfers log messages from application thread (producer) to dedicated logging thread (consumer)
- **Key Features**: 
  - Cache-line aligned to prevent false sharing
  - Memory-efficient circular buffer design
  - Non-blocking operations with try_emplace/try_push variants

### 2. **Memory-Mapped Writer** (`src/mmap_writer.cpp`, `include/mmap_writer.hpp`)
- **Purpose**: High-performance file I/O using memory mapping instead of traditional file operations
- **Benefits**: Direct memory access to files, reducing system call overhead
- **Operations**:
  - `mmap_create()`: Create and write new log files
  - `mmap_read()`: Read log file contents
  - `mmap_update()`: Update existing log entries
- **Why Important**: Memory mapping is significantly faster than standard file I/O for frequent writes

### 3. **Logger Orchestrator** (`src/logger.cpp`)
- **Purpose**: Main coordinator that integrates queue, parser, and writer components
- **Responsibilities**:
  - Message formatting using C++20 std::format
  - Log level management (TRACE, WARN, ERROR, CRITICAL)
  - Queue management and message routing
  - Error handling and system coordination

### 4. **SIMD Parser** (`src/simd_parser.cpp`)
- **Purpose**: Vectorized string operations for processing multiple characters simultaneously
- **Target**: Process 4-16 characters at once instead of character-by-character
- **Status**: Currently skeleton implementation (optimization target for v2)

## Current Architecture Flow
```
Application Thread (Producer)
    ↓
LogInfo Creation (with std::format)
    ↓
SPSC Queue (thread-safe handoff)
    ↓
Consumer Processing
    ↓
Memory-Mapped File Write
    ↓
Persistent Storage
```

## How to Build and Test

### Prerequisites
- CMake 3.15+
- C++20 compatible compiler
- Google Test (for unit tests)

### Build Steps
```bash
# Clean build first to remove previously built files
rm -rf build

# Configure with CMake
cmake -S . -B build

# Build all components
cmake --build build
```

### Test the Minimal Logger
```bash
# Run the basic logger demo
./build/logger

# Expected output:
# Test log size will be mentioned twice
# User "Whoever inputted logged in from IP 192.168.1.1

# Verify the log file was created
ls -la test.log
cat test.log
# Should show: "User" Name logged in from IP 192.168.1.1"
```

### Run Unit Tests
```bash
# Test the SPSC queue implementation
./build/test

# Test individual mmap operations
./build/mmap_create test_file.txt "Hello World"
./build/mmap_read test_file.txt
./build/mmap_update test_file.txt "Updated message"
```

## Current Status: ~65% Complete

### **The Current Working Components:**
- SPSC queue (fully functional, lock-free)
- Memory-mapped file I/O (create, read, update)
- Basic message formatting with C++20 std::format
- LogInfo struct with timestamp and message fields
- CMake build system
- Unit tests for core components

### **In Development:**
- Thread management (producer/consumer threads)
- Proper timestamp handling and serialization
- Queue overflow and error handling
- Configuration system for log levels and file rotation

### **Planned Features:**
- SIMD-optimized string processing
- Batch processing for multiple messages
- File rotation policies
- Memory pool allocation
- Performance benchmarking

## Key Performance Features

1. **Lock-Free Design**: SPSC queue eliminates mutex overhead
2. **Memory Mapping**: Direct memory access bypasses kernel buffer copies
3. **Zero-Copy Architecture**: Messages move through queue without copying
4. **Cache-Friendly**: Data structures aligned to prevent false sharing
5. **Vectorization Ready**: SIMD parser foundation for parallel string operations

## Main Value Proposition of creating this high performance logging system
1. **The Problem**: Traditional logging is slow due to I/O blocking and thread contention
2. **The Solution**: Separate producer/consumer threads with lock-free communication
3. **The Innovation**: Memory mapping + SPSC queue + eventual SIMD processing
4. **The Result**: Sub-microsecond logging latency for high-throughput applications

The current implementation demonstrates the core concept with a working end-to-end pipeline from log creation to file persistence.
