#include "terminal.hpp"

#include <ncurses.h>

#include <csignal>
#include <cstdint>
#include <cstdio>
#include <iostream>

static void handle_exit(int32_t sig) { std::exit(0); }

void terminal_init() {
    initscr();
    raw();
    keypad(stdscr, TRUE);
    noecho();

    curs_set(0);  // hide cursor
    timeout(0);   // don't allow delay for keypresses

    std::signal(SIGINT, handle_exit);
}

void terminal_destroy() {
    endwin();
    std::exit(0);
}