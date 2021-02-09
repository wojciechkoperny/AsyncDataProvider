add_library(vanillaThreads
    src/DataInterface.cpp
    src/Dispatcher.cpp
    src/DataCache.cpp
)

target_include_directories(vanillaThreads
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_link_libraries(vanillaThreads
    PUBLIC
        -Wl,--no-as-needed -lpthread -Wl,--as-needed # Because gcc is dumb and cannot figure out that promise/future requires pthread..
        code_coverage
        compiler_warnings
)


add_executable(vanillaThreads_tests
    tests/DataInterface_test.cpp
)

target_link_libraries(vanillaThreads_tests
    vanillaThreads
    test_runner
)

add_test(vanillaThreads vanillaThreads_tests)
