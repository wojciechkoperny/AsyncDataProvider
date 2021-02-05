cmake_minimum_required(VERSION 3.10)
project(test_proj VERSION 1.0)

include(cmake/CompilerWarnings.cmake)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/inc)

#SET(CMAKE_GENERATOR Unix Makefiles)

if(NOT CMAKE_BUILD_TYPE) 
set(CMAKE_BUILD_TYPE Debug)
endif()
message("Build type: ${CMAKE_BUILD_TYPE}")

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

#message("project source dir"${PROJECT_SOURCE_DIR})
#message("current source dir"${CMAKE_CURRENT_SOURCE_DIR})

add_library(vanillaThreads STATIC ${CMAKE_CURRENT_SOURCE_DIR}/VanillaThreads/vThreads.cpp)
target_include_directories(vanillaThreads PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/VanillaThreads/)
target_link_libraries(vanillaThreads PRIVATE pthread)

add_library(DataProvider STATIC ${CMAKE_CURRENT_SOURCE_DIR}/DataProvider/Dispacher.cpp)
target_include_directories(DataProvider PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/DataProvider/)

add_executable(test_proj1 1__main.cpp)

target_link_libraries(test_proj1 
    vanillaThreads
    DataProvider
    project_settings)

target_compile_features(test_proj1 PUBLIC cxx_std_17)
#set_property(TARGET test_proj1 PROPERTY CXX_STANDARD 17)
#target_include_directories(test_proj1 ${CMAKE_CURRENT_SOURCE_DIRl}/lib_betterpt/) 

#set_project_warnings(test_proj1)