# file(GLOB Containers_SRC CONFIGURE_DEPENDS "*.cpp" "*.hpp")

# add_library(
#     Containers
#     STATIC
#     ${Containers_SRC}
# )

if(BUILD_UNIT_TESTS)
    add_subdirectory(test)
endif()

if(BUILD_BENCHMARKS)
    add_subdirectory(benchmark)
endif()
