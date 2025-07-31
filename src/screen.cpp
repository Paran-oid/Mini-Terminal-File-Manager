#include "screen.hpp"

#include <ncurses.h>

void TFMScreen::update_dimensions() {
    getmaxyx(stdscr, m_screen.rows, m_screen.cols);
}
