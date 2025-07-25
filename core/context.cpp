#include "context.hpp"

#include <ncurses.h>

#include <csignal>
#include <iostream>

#include "builtins.hpp"

void ncurses_init() {
    initscr();
    echo();
    keypad(stdscr, TRUE);
}

void ncurses_destroy() { endwin(); }

static void signal_handler(int32_t signal) {
    endwin();
    std::exit(EXIT_SUCCESS);
}

void signals_remap() {
    struct sigaction sa;
    sa.sa_handler = signal_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;

    sigaction(SIGINT, &sa, nullptr);
    sigaction(SIGINT, &sa, nullptr);   // Ctrl+C
    sigaction(SIGTERM, &sa, nullptr);  // kill <pid>
    sigaction(SIGHUP, &sa, nullptr);   // terminal hangup
    sigaction(SIGQUIT, &sa, nullptr);  // Ctrl+
    sigaction(SIGSEGV, &sa, nullptr);  // segmentation fault
    sigaction(SIGABRT, &sa, nullptr);  // abort()
    sigaction(SIGFPE, &sa, nullptr);   // division by zero, etc.
}