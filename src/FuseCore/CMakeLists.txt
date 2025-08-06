add_library(FuseCore STATIC)
add_library(Fuse::Core ALIAS FuseCore)

target_sources(FuseCore
    PRIVATE
        math/Mat4.cpp
        math/Mat4.h
        math/Vec4.h
)

target_include_directories(FuseCore
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/..>
)
