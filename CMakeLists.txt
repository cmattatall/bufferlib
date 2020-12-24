# @author Carl Mattatall (cmattatall2@gmail.com)
# THE NAME OF THE CMAKE PROJECT IS 
# DETERMINED BY THE NAME OF ITS CONTAINING FOLDER
#
# THIS WAY, TO INCLUDE AND LINK AGAINST THE LIBRARY FROM A HIGHER-LEVEL,
# YOU JUST DO
#
# add_subdirectory(>NAME_OF_THE_PROJECT_DIRECTORY<)
# target_link_libraries(TARGET_TO_LINK_INTO [PUBLIC/PRIVATE/INTERFACE] >NAME_OF_PROJECT_DIRECTORY<)
#
cmake_minimum_required(VERSION 3.16)

get_filename_component(MY_PROJECT_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)

################################################################################
#  OPTIONS GO HERE
################################################################################
option(BUILD_TESTING "[ON/OFF] Option to build tests or not" OFF)
option(BUILD_THREAD_SAFE "[ON/OFF]")

project(
    "${MY_PROJECT_NAME}"
    VERSION 1.0
    DESCRIPTION "EXAMPLE PROJECT FOR CMAKE PROJECT TEMPLATE REPOSITORY"
    LANGUAGES C CXX
)



################################################################################
# BUILD TYPE STUFF
################################################################################
set(SUPPORTED_BUILD_TYPES "")
list(APPEND SUPPORTED_BUILD_TYPES "Debug")
list(APPEND SUPPORTED_BUILD_TYPES "Release")
list(APPEND SUPPORTED_BUILD_TYPES "MinSizeRel")
list(APPEND SUPPORTED_BUILD_TYPES "RelWithDebInfo")
set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS ${SUPPORTED_BUILD_TYPES})
if(NOT CMAKE_BUILD_TYPE)
set(CMAKE_BUILD_TYPE "Debug" CACHE STRING "Build type chosen by the user at configure time" FORCE)
endif(NOT CMAKE_BUILD_TYPE)


################################################################################
# DETECT SOURCES RECURSIVELY FROM src FOLDER AND ADD TO BUILD TARGET
################################################################################
set(LIB "${PROJECT_NAME}") # this is PROJECT_NAME, NOT CMAKE_PROJECT_NAME
message("CONFIGURING TARGET : ${LIB}")
add_library(${LIB})
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
file(GLOB_RECURSE ${LIB}_sources "${CMAKE_CURRENT_SOURCE_DIR}/src/*.c")
target_sources(${LIB} PRIVATE ${${LIB}_sources})


################################################################################
# DETECT PRIVATE HEADERS RECURSIVELY FROM src FOLDER
################################################################################
file(GLOB_RECURSE ${LIB}_private_headers "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h")
set(${LIB}_private_include_directories "")
foreach(hdr ${${LIB}_private_headers})
    get_filename_component(hdr_dir ${hdr} DIRECTORY)
    list(APPEND ${LIB}_private_include_directories ${hdr_dir})
endforeach(hdr ${${LIB}_private_headers})
list(REMOVE_DUPLICATES ${LIB}_private_include_directories)
target_include_directories(${LIB} PRIVATE ${${LIB}_private_include_directories})

################################################################################
# DETECT PUBLIC HEADERS RECURSIVELY FROM inc FOLDER
################################################################################
file(GLOB_RECURSE ${LIB}_public_headers "${CMAKE_CURRENT_SOURCE_DIR}/inc/*.h")
set(${LIB}_public_include_directories "")
foreach(hdr ${${LIB}_public_headers})
    get_filename_component(hdr_dir ${hdr} DIRECTORY)
    list(APPEND ${LIB}_public_include_directories ${hdr_dir})
endforeach(hdr ${${LIB}_public_headers})
list(REMOVE_DUPLICATES ${LIB}_public_include_directories)
target_include_directories(${LIB} PUBLIC ${${LIB}_public_include_directories})

################################################################################
# TEST CONFIGURATION
################################################################################
if(BUILD_TESTING)
    enable_testing()
    include(CTest)
    add_subdirectory(test)
else()
    if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
        enable_testing()
        include(CTest)
        add_subdirectory(test)
    endif()
endif()


################################################################################
# LINK AGAINST THE NECESSARY LIBRARIES BELOW (USER CAN START ADDING STUFF NOW)
################################################################################


######################################
# LINK AGAINST PTHREAD
######################################
if(BUILD_THREAD_SAFE)
    target_compile_definitions(${LIB} PRIVATE "BUFFERLIB_THREAD_SAFE")
    find_package(Threads REQUIRED)
    if(Threads_FOUND) 
        if(WIN32)
            if(CMAKE_USE_WIN32_THREADS_INIT)
                target_link_libraries(${LIB} PUBLIC pthread)
                target_compile_options(${LIB} PUBLIC "-lpthread")
            else()
                message(FATAL_ERROR "Could not find win32 threads")
            endif()
        elseif(UNIX)
            if(CMAKE_USE_PTHREADS_INIT)
                target_link_libraries(${LIB} PUBLIC pthread)
                target_compile_options(${LIB} PUBLIC "-lpthread")
            else()
                message(FATAL_ERROR "Could not find pthreads")
            endif()
        endif()
    else()
        message(FATAL_ERROR "No threading libraries have been found. Aborting!")
    endif()
endif(BUILD_THREAD_SAFE)
















