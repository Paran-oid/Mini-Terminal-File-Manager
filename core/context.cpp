#include "context.hpp"

#include <ncurses.h>

void ncurses_init() {
    initscr();
    echo();
    keypad(stdscr, TRUE);
}

void ncurses_destroy() { endwin(); }