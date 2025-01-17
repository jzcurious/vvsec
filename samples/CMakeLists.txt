cmake_minimum_required(VERSION 3.30)
project(vvsec-samples LANGUAGES CXX)

include(FetchContent)

FetchContent_Declare(
  txt2tok
  GIT_REPOSITORY https://github.com/jzcurious/txt2tok.git
  GIT_TAG v1.0.0
)
FetchContent_MakeAvailable(txt2tok)

file(GLOB_RECURSE SRC
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
)
add_executable(vvsec-samples ${SRC})

target_include_directories(vvsec-samples PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include/
)
target_link_libraries(vvsec-samples PRIVATE
    txt2tok
    vvsec
)
