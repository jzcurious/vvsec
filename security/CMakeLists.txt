cmake_minimum_required(VERSION 3.24)
project(vvsec-security LANGUAGES CXX)

file(GLOB_RECURSE SRC
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
)
add_executable(vvsec-security ${SRC})

target_include_directories(vvsec-security PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include/
)
target_link_libraries(vvsec-security PRIVATE
    vvsec
)
