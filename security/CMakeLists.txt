cmake_minimum_required(VERSION 3.24)
project(proj-security LANGUAGES CXX)

file(GLOB_RECURSE SRC
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
)
add_executable(proj-security ${SRC})

target_include_directories(proj-security PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include/
)
target_link_libraries(proj-security PRIVATE
    proj
)
