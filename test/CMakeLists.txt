macro(create_test single_sourcefile_name)
    add_executable(${single_sourcefile_name}_EXE)
    target_sources(${single_sourcefile_name}_EXE PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/${single_sourcefile_name}.c")
    target_link_libraries(${single_sourcefile_name}_EXE PUBLIC BUFFERLIB)
    add_test(
        ${single_sourcefile_name}_TEST ${single_sourcefile_name}_EXE
        COMMAND ${single_sourcefile_name}_EXE
        --build-generator "${CMAKE_GENERATOR}"
        --test-command "${CMAKE_CTEST_COMMAND}"
    )
endmacro(create_test single_sourcefile_name)



if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)

    create_test(read_in_read_out)
    create_test(too_many_reads)
    
endif()