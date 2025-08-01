#include "screen.hpp"

#include <ncurses.h>

#include <stdexcept>

void TFMScreen::update_dimensions() {
    getmaxyx(stdscr, m_screen.rows, m_screen.cols);
    if (m_screen.rows == -1 || m_screen.cols == -1)
        throw std::runtime_error(
            "TFMScreen: error initalizing rows or/and cols of screen");
}
