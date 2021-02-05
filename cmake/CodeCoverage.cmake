add_library(code_coverage INTERFACE)

option(ENABLE_COVERAGE "Enable coverage reporting for gcc/clang" TRUE)

find_program(GCOVR_PATH NAMES gcovr)
if (NOT GCOVR_PATH)
    message(WARNING "Could not enable code coverage, gcovr not found. Example install: 'sudo pip3 install gcovr'")
else()
    message(STATUS "Found gcovr: ${GCOVR_PATH}")
endif()

if(ENABLE_COVERAGE AND GCOVR_PATH)
    target_compile_options(code_coverage INTERFACE --coverage -O0 -g )
    target_link_libraries(code_coverage INTERFACE --coverage)
endif()
