find_package(EnTT 3.15.0 EXACT CONFIG REQUIRED)

add_library(FuseCore STATIC)
add_library(Fuse::Core ALIAS FuseCore)

fuse_set_compiler_warnings(FuseCore)

target_sources(FuseCore
    PRIVATE
        Event.h
        Event.cpp
        Keyboard.h
        Keyboard.cpp
        Input.h
        Input.cpp
        fileSystem/FileSystem.h
        fileSystem/FileSystem.cpp
        math/Angle.h
        math/Mat4.cpp
        math/Vec3.h
        math/Mat4.h
        math/Vec4.h
        scene/Entity.h
        scene/Scene.h
        scene/Scene.cpp
        scene/NativeScriptSystem.h
        scene/NativeScriptSystem.cpp
        scene/components/CNativeScript.h
        scene/components/Components.h
        utils/TypeTraits.h
        utils/EnumUtils.h
        utils/EnumUtils.inc.h
        utils/EnumFlags.h
        utils/GetTypeName.h
        utils/GetTypeName.inc.h
)

target_link_libraries(FuseCore
    PUBLIC
        EnTT::EnTT
)

target_include_directories(FuseCore
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/..>
)

target_compile_definitions(FuseCore
    PUBLIC
        # platform
        $<$<PLATFORM_ID:Windows>:FUSE_PLATFORM_WINDOWS>
        $<$<PLATFORM_ID:Linux>:FUSE_PLATFORM_LINUX>
        $<$<PLATFORM_ID:Darwin>:FUSE_PLATFORM_OSX>
        # compiler
        $<$<CXX_COMPILER_ID:MSVC>:FUSE_COMPILER_MSVC>
        $<$<CXX_COMPILER_ID:GNU>:FUSE_COMPILER_GCC>
        $<$<CXX_COMPILER_ID:Clang>:FUSE_COMPILER_CLANG>
    PRIVATE
        $<$<PLATFORM_ID:Windows>:WIN32_LEAN_AND_MEAN>
        $<$<PLATFORM_ID:Windows>:NOMINMAX>
    #ENTT_NOEXCEPTION
        #ENTT_USE_ATOMIC
        #ENTT_ID_TYPE
        #ENTT_SPARSE_PAGE
        #ENTT_PACKED_PAGE
        #ENTT_ASSERT
        ##ENTT_ASSERT_CONSTEXPR
        #ENTT_DISABLE_ASSERT
        #ENTT_NO_ETO
        #ENTT_STANDARD_CPP
)
