cmake_minimum_required(VERSION 3.31)
project(DataStructures_CPP)

# GoogleTest requires at least C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/heads/main.zip
)
FetchContent_MakeAvailable(googletest)

enable_testing()

# include headers
include_directories(include)

# defining source files
set(SOURCES
    src/temp.cpp
)

# adding source files
add_library(DataStructures ${SOURCES})

# defining test files
set(TESTS
    tests/AVLTest.cpp
    tests/main.cpp
)

# adding test executable
add_executable(DataStructures_Test
    ${TESTS}
    ${SOURCES}
)

target_link_libraries(DataStructures_Test gtest_main DataStructures)
include(GoogleTest)
gtest_discover_tests(DataStructures_Test)