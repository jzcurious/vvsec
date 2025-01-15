cmake_minimum_required(VERSION 3.30)
project(vvsec-tests LANGUAGES CXX)

include(GoogleTest)
include(FetchContent)

FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG v1.15.2
)
FetchContent_MakeAvailable(googletest)

FetchContent_Declare(
  txt2tok
  GIT_REPOSITORY https://github.com/jzcurious/txt2tok.git
  GIT_TAG v1.0.0
)
FetchContent_MakeAvailable(txt2tok)

file(GLOB_RECURSE SRC
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
)
add_executable(vvsec-tests ${SRC})

target_include_directories(vvsec-tests PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include/
)
target_link_libraries(vvsec-tests PRIVATE
    vvsec
    GTest::gtest_main
    txt2tok
)

enable_testing()
gtest_discover_tests(vvsec-tests)
