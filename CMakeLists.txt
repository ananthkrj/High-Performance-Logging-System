cmake_minimum_required(VERSION 3.15...4.1.0)

project(MyProject VERSION 1.0
                  DESCRIPTION "testing spsc queue"
                  LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

find_package(GTest REQUIRED)

# lanch spsc queue test
add_executable(test tests/test_spsc_queue.cpp)
# target include directories adds an include directory to the target
target_include_directories(test PRIVATE include)
target_link_libraries(test GTest::GTest GTest::Main pthread)

# launch mmap writer functionality
# add_executable(all_mmap src/mmap_create.cpp
#   src/mmap_read.cpp
#    src/mmap_update.cpp
#)

# test mmap functions indiviudally first
add_executable(mmap_create src/mmap_create.cpp)
add_executable(mmap_read src/mmap_read.cpp)
add_executable(mmap_update src/mmap_update.cpp)
# How to launch and test the mmap operations
# cmake --build build
# ./build mmap_create fulltest.txt "message"
# ./build mmap_read fulltest.txt
# ./build mmap_update
# Tests for all mmap operations fully work, however need to fix update
# a little bit. Output text gets weird, and null. Or file cannot be displayed

# How to launch and run lldb
# cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
# cmake --build build
# ./build/test  
# lldb build/test

# how the hell do i compile 
