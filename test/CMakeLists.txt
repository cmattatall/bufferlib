cmake_minimum_required(VERSION 3.18)

add_executable(leakcheck)
target_sources(leakcheck PRIVATE "leakcheck.c")
target_link_libraries(leakcheck PUBLIC BUFFERLIB)
add_test(
    leakcheck_TEST leakcheck
    COMMAND valgrind leakcheck --leak-check=full
    --build-generator "${CMAKE_GENERATOR}"
    --test-command "${CMAKE_CTEST_COMMAND}"
)

add_executable(read_in_read_out)
target_sources(read_in_read_out PRIVATE "read_in_read_out.c")
target_link_libraries(read_in_read_out PUBLIC BUFFERLIB)
add_test(
    read_in_read_out_TEST read_in_read_out
    COMMAND read_in_read_out
    --build-generator "${CMAKE_GENERATOR}"
    --test-command "${CMAKE_CTEST_COMMAND}"
)

add_executable(too_many_reads)
target_sources(too_many_reads PRIVATE "too_many_reads.c")
target_link_libraries(too_many_reads PUBLIC BUFFERLIB)
add_test(
    too_many_reads_TEST too_many_reads
    COMMAND too_many_reads
    --build-generator "${CMAKE_GENERATOR}"
    --test-command "${CMAKE_CTEST_COMMAND}"
)
