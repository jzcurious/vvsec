cmake_minimum_required(VERSION 3.30)
project(vvsec LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 23)

add_subdirectory(vvsec)
add_subdirectory(samples)
add_subdirectory(tests)
# add_subdirectory(benchmarks)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    message(STATUS "Sanitizer is enabled")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pedantic -O0 -g -fsanitize=address")
    # add_subdirectory(security)
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pedantic -O3")
endif()
