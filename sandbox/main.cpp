#include <SDL3/SDL.h>
#include <SDL3/SDL_opengl.h>

#include <print>

int main() {
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS);


    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

    const SDL_WindowFlags windowFlags = SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL;
    SDL_Window*           window = SDL_CreateWindow("FuseEngine Sandbox", 800, 600, windowFlags);
    if (!window) {
        std::println("Failed to create SDL window: {}", SDL_GetError());
        return -1;
    }

    SDL_GLContext glContext = SDL_GL_CreateContext(window);
    if (!glContext) {
        std::println("Failed to create OpenGL Context: {}", SDL_GetError());
        return -1;
    }

    //Use Vsync
    if (SDL_GL_SetSwapInterval(1) < 0) {
        printf("Warning: Unable to set VSync! SDL Error: %s\n", SDL_GetError());
    }

    bool done = false;
    while (!done) {
        SDL_Event event{};
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                done = true;
            }
            if (event.type == SDL_EVENT_WINDOW_RESIZED) {
                auto& windowEvent = event.window;
                glViewport(0, 0, windowEvent.data1, windowEvent.data2);
            }
        }
        glClearColor(.2, .2, .2, 1);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        SDL_GL_SwapWindow(window);
    }

    SDL_GL_DestroyContext(glContext);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
