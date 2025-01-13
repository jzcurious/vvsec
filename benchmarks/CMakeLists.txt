cmake_minimum_required(VERSION 3.24)
project(proj-benchmarks LANGUAGES CXX)

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
add_executable(proj-benchmarks ${SRC})

target_include_directories(proj-benchmarks PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include/
)
target_link_libraries(proj-benchmarks PRIVATE
    proj
    benchmark::benchmark
)
