file(GLOB bench_SRC CONFIGURE_DEPENDS "*.cpp")

foreach(benchmark_file ${bench_SRC})
  get_filename_component(benchmark_name ${benchmark_file} NAME_WE)

  add_executable(
    ${benchmark_name}
    ${benchmark_file}
  )

  target_include_directories(
    ${benchmark_name}
    PUBLIC
      ${PROJECT_SOURCE_DIR}/include/
  )

  target_link_libraries(
      ${benchmark_name}
      PUBLIC
        benchmark::benchmark
        pthread
        project_warnings
        code_sanitizers
  )

  set_target_properties(
    ${benchmark_name}
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/benchmark"
  )
endforeach()