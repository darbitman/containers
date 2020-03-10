function(CompileTests libraries include_dirs executable_output_dir)
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
      "${include_dirs}"
    )

    target_link_libraries(
      ${test_name}
      PUBLIC
      "${libraries}"
    )

    set_target_properties(
      ${test_name}
      PROPERTIES
      RUNTIME_OUTPUT_DIRECTORY "${executable_output_dir}"
    )
  endforeach()
endfunction()