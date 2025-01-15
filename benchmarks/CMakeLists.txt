cmake_minimum_required(VERSION 3.30)
project(vvsec-benchmarks LANGUAGES CXX)

include(FetchContent)

FetchContent_Declare(
  benchmark
  GIT_REPOSITORY https://github.com/google/benchmark.git
  GIT_TAG v1.9.1
)
FetchContent_MakeAvailable(benchmark)

file(GLOB_RECURSE SRC
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
)
add_executable(vvsec-benchmarks ${SRC})

target_include_directories(vvsec-benchmarks PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include/
)
target_link_libraries(vvsec-benchmarks PRIVATE
    vvsec
    benchmark::benchmark
)
