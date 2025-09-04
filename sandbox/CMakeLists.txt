
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
)
