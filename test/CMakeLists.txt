set(
  libraries
  GTest::Main
  GTest::GTest
  pthread
)

set(additional_compiler_flags)

if(ENABLE_CODE_COVERAGE)
  list(APPEND libraries gcov "--coverage")
  list(APPEND additional_compiler_flags -fprofile-arcs -ftest-coverage)
endif()

message("${libraries}")
message("${additional_compiler_flags}")

set(include_dirs ${PROJECT_SOURCE_DIR}/include/)


CompileTests("${libraries}" "${include_dirs}" "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/test" "${additional_compiler_flags}")