#include "render.hpp"

#include <ncurses.h>

uint8_t TFM_screen_refresh(TFM_Context& context) {
    std::vector<std::string> input_buf = context.input_buf_get();
    while (!input_buf.empty()) {
        printw("%s", input_buf.back().c_str());
        input_buf.pop_back();
    }
    printw("%s:_$ ", context.working_dir_get().string().c_str());
    return EXIT_SUCCESS;
}