cmake_minimum_required(VERSION 3.24)
project(vvsec-lib LANGUAGES CXX)

include(FetchContent)

FetchContent_Declare(
  dep
  GIT_REPOSITORY https://github.com/jzcurious/dep.git
  GIT_TAG v1.0.0
)
FetchContent_MakeAvailable(dep)

file(GLOB_RECURSE SRC
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
)
add_library(vvsec-lib STATIC ${SRC})

target_compile_definitions(vvsec-lib PRIVATE
    "DEBUG=$<CONFIG:Debug>"
)
target_include_directories(vvsec-lib PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include/
)
target_link_libraries(vvsec-lib PUBLIC
    dep
)
