#include "config.hpp"

#include <ncurses.h>

void _die(const std::string& filename, int32_t line,
          const std::string& message) {
    endwin();
    fprintf(stderr, "Error at %s:%d: %s\n", filename.c_str(), line,
            message.c_str());
    std::exit(1);
}

void TFMConfig::screen_dimensions_update() {
    getmaxyx(stdscr, m_screen.rows, m_screen.cols);
}

void TFMConfig::append_row(const std::string& content) {
    m_rows.push_back(content);
}