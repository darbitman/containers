cmake_minimum_required(VERSION 3.9)

project(helpers)

set(PROJECT_BINARY_DIR ${PROJECT_SOURCE_DIR}/build)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)

set(CMAKE_CXX_STANDARD 17)

# add warnings to all build types
set(WARNING_FLAGS "-Wall -Wextra -Wshadow -Wdouble-promotion")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${WARNING_FLAGS}")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${WARNING_FLAGS}")

# Use GTest::Main and GTest::GTest when linking libraries
find_package(GTest)
if(GTEST_FOUND)
    set(BUILD_UNIT_TESTS ON)
    include (CTest)
else()
    message(WARNING "GTest not found in system path. Not building unit tests.")
endif()

# use benchmark::benchmark when linking libraries
find_package(benchmark)
if(benchmark_FOUND)
    set(BUILD_BENCHMARKS ON)
else()
    message(WARNING "benchmark not found in system path. Not building benchmarks.")
endif()

# link time optimization/interprocedural optimization
cmake_policy(SET CMP0069 NEW)
include(CheckIPOSupported)
check_ipo_supported(RESULT IsIpoSupported)
if(IsIpoSupported)
    set(CMAKE_INTERPROCEDURAL_OPTIMIZATION TRUE)
else()
    message(WARNING "IPO Not Supported")
endif()

add_subdirectory(src)

if(BUILD_BENCHMARKS)
    add_subdirectory(benchmark)
endif()
