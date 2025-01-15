cmake_minimum_required(VERSION 3.30)
project(vvsec-lib LANGUAGES CXX)

add_library(vvsec INTERFACE)

target_include_directories(vvsec INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/include/
)
