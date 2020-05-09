set(
  libraries
  GTest::Main
  GTest::GTest
  pthread
  gcov
  "--coverage"
)

set(include_dirs ${PROJECT_SOURCE_DIR}/include/)

set(additional -fprofile-arcs -ftest-coverage)
CompileTests("${libraries}" "${include_dirs}" "${EXECUTABLE_OUTPUT_PATH}/test" "${additional}")
