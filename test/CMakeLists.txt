macro(create_basic_test single_sourcefile_name)
    add_executable(${single_sourcefile_name})
    target_sources(${single_sourcefile_name} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/${single_sourcefile_name}.c")
    target_link_libraries(${single_sourcefile_name} PUBLIC BUFFERLIB)
    add_test(
        ${single_sourcefile_name}_TEST ${single_sourcefile_name}
        COMMAND ${single_sourcefile_name}
        --build-generator "${CMAKE_GENERATOR}"
        --test-command "${CMAKE_CTEST_COMMAND}"
    )
endmacro(create_basic_test single_sourcefile_name)


if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    
    add_executable(leakcheck)
    target_sources(leakcheck PRIVATE leakcheck.c)
    target_link_libraries(leakcheck PUBLIC BUFFERLIB)
    add_test(
        leakcheck_TEST leakcheck
        # this test is special because requires valgrind
        COMMAND valgrind leakcheck 
        --build-generator "${CMAKE_GENERATOR}"
        --test-command "${CMAKE_CTEST_COMMAND}"
    )

    create_basic_test(read_in_read_out)
    create_basic_test(too_many_reads)

endif()