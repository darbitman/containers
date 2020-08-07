set(
  libraries
  GTest::Main
  GTest::GTest
  pthread
  project_warnings
  code_coverage
)

set(include_dirs ${PROJECT_SOURCE_DIR}/include/)

CompileTests("${libraries}" "${include_dirs}" "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/test" "${additional_compiler_flags}")