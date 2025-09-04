find_package(SDL3 3.2.18 EXACT CONFIG REQUIRED)
find_package(glad 0.1.36 EXACT CONFIG REQUIRED)
find_package(OpenGL REQUIRED)

add_executable(sandbox
    main.cpp
    Application.h
    Application.cpp
    Camera.h
    Camera.cpp
)

fuse_set_compiler_warnings(sandbox)

target_link_libraries(sandbox
    PUBLIC
        Fuse::App
        SDL3::SDL3
        glad::glad
)
