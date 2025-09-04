add_library(FuseCore STATIC)
add_library(Fuse::Core ALIAS FuseCore)

fuse_set_compiler_warnings(FuseCore)

target_sources(FuseCore
    PRIVATE
        math/Angle.h
        math/Mat4.cpp
        math/Vec3.h
        math/Mat4.h
        math/Vec4.h
        utils/TypeTraits.h
        utils/EnumUtils.h
        utils/EnumUtils.inc.h
        utils/EnumFlags.h
        utils/GetTypeName.h
        utils/GetTypeName.inc.h
)

target_include_directories(FuseCore
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/..>
)
