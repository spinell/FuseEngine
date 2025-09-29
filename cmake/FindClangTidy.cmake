SET(CLANG_TIDY_VERSION_REQUIRED 19)

#
# Try to find clang-format
#
if(DEFINED CLANG_TIDY_EXECUTABLE AND NOT EXISTS ${CLANG_TIDY_EXECUTABLE})
    message(FATAL_ERROR "CLANG_TIDY_EXECUTABLE is defined by can't be found '${CLANG_TIDY_EXECUTABLE}'.")
endif()

# clang-tidy was not specified with -DCLANG_TIDY_EXECUTABLE=...
# try to find it ...
if(NOT DEFINED CLANG_TIDY_EXECUTABLE)
    find_program(CLANG_TIDY_EXECUTABLE
        NAMES
            clang-tidy-${CLANG_TIDY_VERSION_REQUIRED}
            clang-tidy
    )
    if(CLANG_TIDY_EXECUTABLE-NOTFOUND)
        message(FATAL_ERROR "clang-tidy not found!")
    endif()
    message(STATUS "Found clang-tidy in:  ${CLANG_TIDY_EXECUTABLE}")
else()
    message(STATUS "Using clang-tidy in:  ${CLANG_TIDY_EXECUTABLE}")
endif()


#
# Check clang-tidy version
#
execute_process(COMMAND ${CLANG_TIDY_EXECUTABLE} --version OUTPUT_VARIABLE CLANG_TIDY_VERSION_FOUND)
string(REGEX MATCH "LLVM version ([0-9]+)" CLANG_TIDY_VERSION_FOUND ${CLANG_TIDY_VERSION_FOUND})
unset(CLANG_TIDY_VERSION_FOUND)
if(NOT CMAKE_MATCH_1 EQUAL ${CLANG_TIDY_VERSION_REQUIRED})
    message(FATAL_ERROR "clang-tidy version ${CMAKE_MATCH_1} not supported. Must use version ${CLANG_TIDY_VERSION_REQUIRED}")
endif()
