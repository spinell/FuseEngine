#include "SandboxApplication.h"
#include "FuseApp/SDL3/SDL3Helper.h"
#include "FuseApp/Window.h"

#include <spdlog/spdlog.h>

#include <cstdlib> // Required for atoi
#include <memory>
#include <ranges> // Required for std::views::split
#include <string_view>

namespace {

#ifdef TODO
// from https://wiki.libsdl.org/SDL3/SDL_CreateCursor
/* XPM */
constexpr const char* kArrow[] = {
  /* width height num_colors chars_per_pixel */
  "    32    32        3            1",
  /* colors */
  "X c #000000",
  ". c #ffffff",
  "  c None",
  /* pixels */
  "X                               ",
  "XX                              ",
  "X.X                             ",
  "X..X                            ",
  "X...X                           ",
  "X....X                          ",
  "X.....X                         ",
  "X......X                        ",
  "X.......X                       ",
  "X........X                      ",
  "X.....XXXXX                     ",
  "X..X..X                         ",
  "X.X X..X                        ",
  "XX  X..X                        ",
  "X    X..X                       ",
  "     X..X                       ",
  "      X..X                      ",
  "      X..X                      ",
  "       XX                       ",
  "                                ",
  "                                ",
  "                                ",
  "                                ",
  "                                ",
  "                                ",
  "                                ",
  "                                ",
  "                                ",
  "                                ",
  "                                ",
  "                                ",
  "                                ",
  "0,0"};

SDL_Cursor* init_system_cursor(const char* const image[]) {
    int   i   = 0;
    int   row = 0;
    int   col = 0;
    Uint8 data[4 * 32]{};
    Uint8 mask[4 * 32]{};

    i = -1;
    for (row = 0; row < 32; ++row) {
        for (col = 0; col < 32; ++col) {
            if (col % 8) {
                data[i] <<= 1;
                mask[i] <<= 1;
            } else {
                ++i;
                data[i] = mask[i] = 0;
            }
            if (image[4 + row][col] == 'X') {
                data[i] |= 0x01;
                mask[i] |= 0x01;
            } else if (image[4 + row][col] == '.') {
                mask[i] |= 0x01;
            }
        }
    }

    const std::string_view del      = ",";
    const auto             hotSpots = std::string_view(image[4 + row]);
    const auto             pos      = hotSpots.find(del);
    const auto             hotXStr  = hotSpots.substr(0, pos);
    const auto             hotYStr  = hotSpots.substr(pos + del.size());
    int                    hotX     = 0;
    int                    hotY     = 0;
    std::from_chars(hotXStr.data(), hotXStr.data() + hotXStr.size(), hotX);
    std::from_chars(hotYStr.data(), hotYStr.data() + hotYStr.size(), hotY);

    return SDL_CreateCursor(data, mask, 32, 32, hotX, hotY);
}

#endif

} // namespace

int main() {
    auto app = std::make_unique<Application>();
    app->run();
    app.reset();
    return 0;
}
