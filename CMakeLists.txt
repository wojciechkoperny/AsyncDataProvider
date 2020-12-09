cmake_minimum_required(VERSION 3.17)
project(test_proj VERSION 1.0)

include(cmake/CompilerWarnings.cmake)

#SET(CMAKE_GENERATOR Ninja)

if(NOT CMAKE_BUILD_TYPE) 
set(CMAKE_BUILD_TYPE Release)
else()
    set(CMAKE_BUILD_TYPE)
    endif()
    
    option(TESTBUILD "Build test programs" OFF)
    
if (TESTBUILD)
message("test_build was set")
add_definitions(-DTEST_BUILD)
else()
message("test_build is NOT set")
endif()

add_library(project_settings INTERFACE)
set_project_warnings(project_settings)

#add_library(betterpt lib_betterpt/1.cpp)
#target_include_directories(betterpt PUBLIC ${CMAKE_CURRENT_SOURCE_DIRl}/lib_betterpt/)

add_executable(test_proj1 1__main.cpp)

target_link_libraries(test_proj1 
    pthread
    project_settings
)

#target_include_directories(test_proj1 ${CMAKE_CURRENT_SOURCE_DIRl}/lib_betterpt/) 

#set_project_warnings(test_proj1)