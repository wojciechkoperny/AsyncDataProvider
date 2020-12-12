cmake_minimum_required(VERSION 3.17)
project(test_proj VERSION 1.0)

include(cmake/CompilerWarnings.cmake)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/inc)

#SET(CMAKE_GENERATOR Unix Makefiles)

if(NOT CMAKE_BUILD_TYPE) 
set(CMAKE_BUILD_TYPE Debug)
endif()
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")

option(TESTBUILD "Build test programs" OFF)
    
if (TESTBUILD)
message("-- Test_build was set build without additional compiler flags")
add_definitions(-DTEST_BUILD)
else()
message("-- Test_build is NOT set")
endif()

add_library(project_settings INTERFACE)
if (NOT TESTBUILD)
set_project_warnings(project_settings)
endif()
#set_project_warnings(test_proj1)
#add_library(betterpt lib_betterpt/1.cpp
#target_include_directories(betterpt PUBLIC ${CMAKE_CURRENT_SOURCE_DIRl}/lib_betterpt/)

add_executable(test_proj1 1__main.cpp)

target_link_libraries(test_proj1 
    pthread
    project_settings)

#target_include_directories(test_proj1 ${CMAKE_CURRENT_SOURCE_DIRl}/lib_betterpt/) 

#set_project_warnings(test_proj1)