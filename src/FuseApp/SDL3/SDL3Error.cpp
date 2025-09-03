#include "SDL3Error.h"

#include <SDL3/SDL_error.h>
#include <spdlog/spdlog.h>

namespace fuse::sdl3 {

void CheckSDLError(std::string_view prefix) {
    if (const char* error = SDL_GetError(); *error != '\0') {
        spdlog::error("[{}] SDL Error: {}", prefix, error);
        SDL_ClearError();
    }
}

} // namespace fuse::sdl3
