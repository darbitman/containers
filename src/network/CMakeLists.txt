file(GLOB network_SRC CONFIGURE_DEPENDS "*.cpp" "*.hpp")

add_library(
    network
    STATIC
    ${network_SRC}
)
