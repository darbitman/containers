# file(GLOB Containers_SRC CONFIGURE_DEPENDS "*.cpp" "*.hpp")

# add_library(
#     Containers
#     STATIC
#     ${Containers_SRC}
# )

add_subdirectory(test)
add_subdirectory(bench)
