file(GLOB test_SRC CONFIGURE_DEPENDS "*.cpp")

foreach(test_file ${test_SRC})
  get_filename_component(test_name ${test_file} NAME_WE)

  add_executable(
    ${test_name}
    ${test_file}
  )

  target_include_directories(
    ${test_name}
    PUBLIC
    ${PROJECT_SOURCE_DIR}/src
  )

  target_link_libraries(
    ${test_name}
    PUBLIC
    GTest::Main
    GTest::GTest
    pthread
  )

  add_test(
    NAME ${test_name}
    COMMAND ${test_name}
    WORKING_DIRECTORY ${PROJECT_BINARY_DIR})
endforeach()
