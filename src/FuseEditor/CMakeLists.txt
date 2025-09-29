
add_executable(FuseEditor)
fuse_set_compiler_warnings(FuseEditor)

target_sources(FuseEditor
    PRIVATE
        main.cpp
        EditorApplication.h
        EditorApplication.cpp
        EditorCamera.h
        EditorCamera.cpp
        panel/EditorPanel.h
        panel/LogPanel.h
        panel/LogPanel.cpp
        panel/InspectorPanel.h
        panel/InspectorPanel.cpp
        panel/SceneHierachyPanel.h
        panel/SceneHierachyPanel.cpp
        panel/ScenePanel.cpp
        panel/ScenePanel.h
)

target_link_libraries(
    FuseEditor
    PUBLIC
        Fuse::App
)

target_compile_definitions(FuseEditor
    PRIVATE
        $<$<CXX_COMPILER_ID:MSVC>:WIN32_LEAN_AND_MEAN>
        $<$<CXX_COMPILER_ID:MSVC>:NOMINMAX>
        IMGUI_DEFINE_MATH_OPERATORS
)

add_custom_command(
	TARGET FuseEditor POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/data/fonts ${CMAKE_CURRENT_BINARY_DIR}/fonts
)

install(TARGETS FuseEditor DESTINATION .)
install(DIRECTORY data/fonts DESTINATION .)
