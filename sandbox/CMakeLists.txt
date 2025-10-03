
add_executable(sandbox
    main.cpp
    SandboxApplication.h
    SandboxApplication.cpp
    Camera.h
    Camera.cpp
    PlayerScript.h
    PlayerScript.cpp
)

fuse_set_compiler_warnings(sandbox)

target_link_libraries(sandbox
    PUBLIC
        Fuse::App
)
