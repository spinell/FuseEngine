#pragma once
#include <string_view>

namespace fuse::sdl3 {

/// @brief Print the value of SDL_GetError if any. Than call SDL_ClearError.
/// @param prefix The prefix used when printing the error.
void CheckSDLError(std::string_view prefix);

} // namespace fuse::sdl3
