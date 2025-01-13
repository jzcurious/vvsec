cmake_minimum_required(VERSION 3.24)
project(proj-tests LANGUAGES CXX)

include(GoogleTest)
include(FetchContent)

FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG v1.15.2
)
FetchContent_MakeAvailable(googletest)

file(GLOB_RECURSE SRC
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
)
add_executable(proj-tests ${SRC})

target_include_directories(proj-tests PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include/
)
target_link_libraries(proj-tests PRIVATE
    proj
    GTest::gtest_main
)

enable_testing()
gtest_discover_tests(proj-tests)
