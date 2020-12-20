cmake_minimum_required(VERSION 3.18)

project(
    BUFFERLIB 
    VERSION 1.0 
    DESCRIPTION "STATICALLY ALLOCATED JSON LIBRARY FOR EMBEDDED SYSTEMS. LOOSELY BASED ON JSMN"
    LANGUAGES C
)
set(BUILD_TARGET ${PROJECT_NAME})
message("CONFIGURING TARGET : ${BUILD_TARGET}")
add_library(${BUILD_TARGET})
set(CMAKE_EXPORT_COMPILE_COMMANDS ON) # vscode

set(sources
    "src/ringbuf.c"
)

target_include_directories(${BUILD_TARGET} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")

set(private_include_directories = "${CMAKE_CURRENT_SOURCE_DIR}/inc")

message("private_include_directories = ${private_include_directories}")

target_include_directories(${BUILD_TARGET} PUBLIC ${private_include_directories})

target_sources(${BUILD_TARGET} PRIVATE ${sources})

if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    
    # GENERATE DEBUG SYMBOLS IF WE'RE GOING TO TEST STUFF
    if(NOT CMAKE_BUILD_TYPE)
        set(CMAKE_BUILD_TYPE "Debug")
        target_compile_options(${BUILD_TARGET} PRIVATE "-Wall")
    endif(NOT CMAKE_BUILD_TYPE)

    include(CTest)
    enable_testing()
    add_subdirectory(test)
    option(PACKAGE_TESTS "Build the tests" ON)
endif()
