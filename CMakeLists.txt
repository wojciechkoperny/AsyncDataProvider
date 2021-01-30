cmake_minimum_required(VERSION 3.12)
project(test_proj VERSION 1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(cmake/CompilerWarnings.cmake)
include(cmake/CodeCoverage.cmake)
include(cmake/Ccache.cmake)

add_subdirectory(vanillaThreads)


add_executable(test_exec test.cpp)

target_link_libraries(test_exec 
    vanillaThreads
)