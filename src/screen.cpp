#include "screen.hpp"

#include <ncurses.h>

#include <csignal>
#include <stdexcept>

TFMScreen* TFMScreen::instance = nullptr;

static void handle_exit(int32_t sig) {
    (void)sig;
    std::exit(0);
}

static void window_size_update(int32_t sig) {
    (void)sig;
    if (TFMScreen::instance) {
        TFMScreen::instance->update_dimensions(sig);
    }
}

void TFMScreen::update_dimensions(int32_t sig) {
    (void)sig;
    getmaxyx(stdscr, m_screen.rows, m_screen.cols);
    if (m_screen.rows == -1 || m_screen.cols == -1) {
        throw std::runtime_error(
            "TFMScreen: error initializing screen dimensions");
    }
}

void TFMScreen::terminal_init() {
    initscr();
    raw();

    keypad(stdscr, TRUE);
    noecho();

    instance = this;

    // hide cursor
    // curs_set(0);

    // don't allow delay for keypresses
    // timeout(0);

    std::signal(SIGINT, handle_exit);
    std::signal(SIGWINCH, window_size_update);
}

void TFMScreen::terminal_destroy() {
    endwin();
    std::exit(0);
}