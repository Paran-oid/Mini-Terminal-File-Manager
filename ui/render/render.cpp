#include "render.hpp"

#include <ncurses.h>

#include <algorithm>
#include <cmath>
#include <misc.hpp>

static std::string pad_right(const std::string& s, size_t width) {
    return s + std::string(width - s.size(), ' ');
}

uint8_t TFM_ls_display(TFM_Context& context,
                       std::vector<std::string>& filenames) {
    if (filenames.empty()) return EXIT_SUCCESS;

    // sort files array alphabetically
    std::sort(filenames.begin(), filenames.end());

    // get longest filename
    int32_t max_len = 0;
    for (const std::string& filename : filenames) {
        if (filename.length() > max_len) {
            max_len = filename.size();
        }
    }

    if (max_len == 0) die("invalid array passed as parameter");
    uint8_t padding = 4;

    auto dimensions = context.screen_dimensions_get();
    uint32_t cols = dimensions.second / (max_len + padding);
    int row_count = (filenames.size() + cols - 1) / cols;

    // TODO: make it display correctly
    /*
            maybe use the mouse position from context.hpp
    */
    for (size_t row = 0; row < row_count; row++) {
        for (size_t col = 0; col < cols; col++) {
            uint32_t index = col * row_count + row;

            if (index >= filenames.size()) continue;

            int x = col * (max_len + padding);
            int y = row;

            //  "Print a left-aligned string, padded to a field width given
            //  by an argument."
            mvprintw(y, x, "%-*s", max_len, filenames[index].c_str());
        }
    }
    printw("\n");

    return EXIT_SUCCESS;
}

uint8_t TFM_screen_refresh(TFM_Context& context) {
    std::vector<std::string> input_buf = context.input_buf_get();
    while (!input_buf.empty()) {
        printw("%s", input_buf.back().c_str());
        input_buf.pop_back();
    }
    printw("%s:_$ ", context.working_dir_get().string().c_str());
    return EXIT_SUCCESS;
}