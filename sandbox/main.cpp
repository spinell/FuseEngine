#include <SDL3/SDL.h>

#include <print>

int main() {
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS);

    const SDL_WindowFlags windowFlags = SDL_WINDOW_RESIZABLE;
    SDL_Window*           window = SDL_CreateWindow("FuseEngine Sandbox", 800, 600, windowFlags);
    if (!window) {
        std::println("Failed to create SDL window: {}", SDL_GetError());
        return -1;
    }

    bool done = false;
    while (!done) {
        SDL_Event event{};
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                done = true;
            }
        }
    }

    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
