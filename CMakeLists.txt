cmake_minimum_required(VERSION 3.10)
project(rawlogger VERSION 1.0.0 LANGUAGES C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Find Threads library for pthread
find_package(Threads REQUIRED)

# Include directories
include_directories(include)

# The rawlogger library
add_library(rawlogger src/logger.c src/sink.c)
target_include_directories(rawlogger PUBLIC include)
target_link_libraries(rawlogger PUBLIC Threads::Threads)

# Example executable
add_executable(rawlogger_example examples/main.c)
target_link_libraries(rawlogger_example PRIVATE rawlogger)
