cmake_minimum_required(VERSION 3.17)
project(test_proj VERSION 1.0)

add_executable(test_proj1 1__main.c)
target_link_libraries(test_proj1 pthread)