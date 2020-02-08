add_subdirectory(containers)
add_subdirectory(creators)
add_subdirectory(network)

if(BUILD_UNIT_TESTS)
    add_subdirectory(test)
endif()

if(BUILD_BENCHMARKS)
    add_subdirectory(benchmark)
endif()
