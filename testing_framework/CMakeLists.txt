add_library(test_runner test_runner.cpp)

target_include_directories(test_runner
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)
