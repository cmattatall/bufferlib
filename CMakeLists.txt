cmake_minimum_required(VERSION 3.18)

project(
    BUFFERLIB 
    VERSION 1.0 
    DESCRIPTION "(OPTIONALLY) THREAD-SAFE BUFFER API LIBRARY"
    LANGUAGES C
)
message("CONFIGURING TARGET : ${PROJECT_NAME}")
add_library(${PROJECT_NAME})
set(CMAKE_EXPORT_COMPILE_COMMANDS ON) # vscode

set(sources
    "${CMAKE_CURRENT_SOURCE_DIR}/src/ringbuf.c"
)

target_include_directories(
    ${PROJECT_NAME} 
    PUBLIC 
    "${CMAKE_CURRENT_SOURCE_DIR}" 
    "${CMAKE_CURRENT_SOURCE_DIR}/inc"
)

target_sources(${PROJECT_NAME} PRIVATE ${sources})

# this is a guard so we don't run tests on LITERALLY every library we import
if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    
    # GENERATE DEBUG SYMBOLS IF WE'RE GOING TO TEST STUFF
    if(NOT CMAKE_BUILD_TYPE)
        set(CMAKE_BUILD_TYPE "Debug")
        target_compile_options(${PROJECT_NAME} PRIVATE "-Wall")
    endif(NOT CMAKE_BUILD_TYPE)

    include(CTest)
    enable_testing()
    add_subdirectory(test)
    option(PACKAGE_TESTS "Build the tests" ON)
endif()
