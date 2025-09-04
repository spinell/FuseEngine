find_package(SDL3   3.2.18 EXACT CONFIG REQUIRED)
find_package(spdlog 1.15.3 EXACT CONFIG REQUIRED)
find_package(imgui               CONFIG REQUIRED)

add_library(FuseApp STATIC)
add_library(Fuse::App ALIAS FuseApp)
fuse_set_compiler_warnings(FuseApp)

target_sources(FuseApp
    PRIVATE
        Application.h
        Application.cpp
        Event.h
        Event.cpp
        Keyboard.h
        Keyboard.cpp
        Timer.cpp
        Timer.h
        Window.h
        Window.cpp
        SDL3/SDL3Error.h
        SDL3/SDL3Error.cpp
        SDL3/SDL3Helper.h
        SDL3/SDL3Helper.cpp
)

target_link_libraries(
    FuseApp
    PUBLIC
        Fuse::Core
        SDL3::SDL3
        spdlog::spdlog
        imgui::imgui

)
