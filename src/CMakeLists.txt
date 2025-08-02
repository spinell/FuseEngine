add_library(FuseCore STATIC)
add_library(Fuse::Core ALIAS FuseCore)

target_sources(FuseCore
    PRIVATE
        fuse.cpp
        fuse.h
)

target_include_directories(FuseCore
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
)
