# TEST CREATION SCRIPT
# ALL C FILES IN THIS DIRECTORY WILL BE ADDED TO THE TEST SUITE
# 
# THUS, A TEST SHOULD BE SIMPLE, SINGLE SOURCE FILE with a mainline
# intended to test a very specific feature

cmake_minimum_required(VERSION 3.18)
file(GLOB test_sources "${CMAKE_CURRENT_SOURCE_DIR}/*.c")
foreach(src ${test_sources})
    get_filename_component(test_suffix ${src} NAME_WLE)
    set(test_name "${LIB}_${test_suffix}")
    add_executable(${test_name})
    target_sources(${test_name} PRIVATE ${src})
    target_link_libraries(${test_name} PRIVATE ${LIB})
    add_test(
        NAME ${test_name}_TEST
        COMMAND ${test_name}
        --build-generator "${CMAKE_GENERATOR}"
        --test-command "${CMAKE_CTEST_COMMAND}"
    ) 
endforeach(src ${test_sources})