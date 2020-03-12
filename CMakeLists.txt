cmake_minimum_required(VERSION 3.9)

project(helpers)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin/${CMAKE_BUILD_TYPE})
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib/${CMAKE_BUILD_TYPE})

set(CMAKE_CXX_STANDARD 17)

# add warnings to all build types
set(WARNING_FLAGS "-Wall -Wextra -Wshadow -Wdouble-promotion")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${WARNING_FLAGS}")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${WARNING_FLAGS}")

# ccache to speed up builds
option(ENABLE_CCACHE "Enable ccache to speed up builds" ON)
if(ENABLE_CCACHE)
  find_program(CCACHE ccache)
  if(CCACHE)
    message(STATUS "Found ccache: ${CCACHE}")
    set(CMAKE_CXX_COMPILER_LAUNCHER ${CMAKE_COMMAND} -E env CCACHE_BASEDIR=${PROJECT_SOURCE_DIR} ${CCACHE})
    set(CMAKE_C_COMPILER_LAUNCHER ${CMAKE_COMMAND} -E env CCACHE_BASEDIR=${PROJECT_SOURCE_DIR} ${CCACHE})
  else()
    message(WARNING "ccache not found")
  endif()
endif()

# link time optimization/interprocedural optimization
option(ENABLE_LINK_TIME_OPTIMIZATION "Optimize during link time" ON)
if(ENABLE_LINK_TIME_OPTIMIZATION)
  cmake_policy(SET CMP0069 NEW)
  include(CheckIPOSupported)
  check_ipo_supported(RESULT IsIpoSupported)
  if(IsIpoSupported)
      set(CMAKE_INTERPROCEDURAL_OPTIMIZATION TRUE)
  else()
      message(WARNING "IPO Not Supported")
  endif()
endif()


# Use GTest::Main and GTest::GTest when linking libraries
find_package(GTest)
if(GTEST_FOUND)
    set(BUILD_UNIT_TESTS ON)
    include(cmake/CompileTests.cmake)
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

if(BUILD_UNIT_TESTS)
    add_subdirectory(test)
endif()

if(BUILD_BENCHMARKS)
    add_subdirectory(benchmark)
endif()
