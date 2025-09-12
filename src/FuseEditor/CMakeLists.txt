
add_executable(FuseEditor)
fuse_set_compiler_warnings(FuseEditor)

target_sources(FuseEditor
    PRIVATE
        main.cpp
        EditorApplication.h
        EditorApplication.cpp
        panel/SceneHierachyPanel.h
        panel/SceneHierachyPanel.cpp
)

target_link_libraries(
    FuseEditor
    PUBLIC
        Fuse::App
)
