cmake_minimum_required(VERSION 3.17)
project(test_proj VERSION 1.0)

SET(CMAKE_MAKE_PROGRAM ninja)
option(TESTBUILD "Build test programs" OFF)

if (TESTBUILD)
    message("test_build was set")
    add_definitions(-DTEST_BUILD)
else()
    message("test_build is NOT set")
endif()

add_executable(test_proj1 1__main.c)
target_link_libraries(test_proj1 pthread)