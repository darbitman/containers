set(
  libraries
  GTest::Main
  GTest::GTest
  pthread
)

set(include_dirs ${PROJECT_SOURCE_DIR}/include/)

CompileTests("${libraries}" "${include_dirs}" "${EXECUTABLE_OUTPUT_PATH}/test")
