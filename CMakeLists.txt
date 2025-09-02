cmake_minimum_required(VERSION 3.15...4.1.0)

project(MyProject VERSION 1.0
                  DESCRIPTION "testing spsc queue"
                  LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

find_package(GTest REQUIRED)

add_executable(test tests/test_spsc_queue.cpp)

# target include directories adds an include directory to the target
target_include_directories(test PRIVATE include)

target_link_libraries(test GTest::GTest GTest::Main pthread)


# How to launch lldb