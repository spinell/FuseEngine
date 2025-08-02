#
# Prevent in source build
#

if(CMAKE_SOURCE_DIR STREQUAL CMAKE_BINARY_DIR)
  message(FATAL_ERROR "In-source builds are not supported.\n"
                      " * Delete ${CMAKE_SOURCE_DIR}/CMakeCache.txt\n"
                      " * Delete ${CMAKE_SOURCE_DIR}/CMakeFiles/ directory.\n")
endif()
