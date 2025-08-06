find_package(SDL3 3.2.18 EXACT CONFIG REQUIRED)
find_package(glad 0.1.36 EXACT CONFIG REQUIRED)
find_package(OpenGL REQUIRED)

add_executable(sandbox main.cpp)

target_link_libraries(sandbox
    PUBLIC
        Fuse::Core
        SDL3::SDL3
        glad::glad
)
