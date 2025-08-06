find_package(SDL3 3.2.18 EXACT CONFIG REQUIRED)
find_package(OpenGL REQUIRED)

add_executable(sandbox main.cpp)

target_link_libraries(sandbox
    PUBLIC
        SDL3::SDL3
        OpenGL::GL
)
