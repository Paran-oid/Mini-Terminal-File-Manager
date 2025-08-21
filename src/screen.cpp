#include "screen.hpp"

#include <ncurses.h>

#include <csignal>
#include <stdexcept>

TFMScreen* TFMScreen::ms_instance = nullptr;

void TFMScreen::handle_exit(int32_t sig) {
    (void)sig;
    std::exit(0);
}

void TFMScreen::window_size_update(int32_t sig) {
    (void)sig;
    if (TFMScreen::ms_instance) {
        TFMScreen::ms_instance->update_dimensions(sig);
    }
}

void TFMScreen::update_dimensions(int32_t sig) {
    (void)sig;
    int32_t rows, cols;
    getmaxyx(stdscr, rows, cols);

    if (rows == -1 || cols == -1) {
        throw std::runtime_error(
            "TFMScreen: error initializing screen dimensions");
    }

    m_app_screen.rows = static_cast<size_t>(rows);
    m_app_screen.cols = static_cast<size_t>(cols);

    wresize(stdscr, rows, cols);
    wrefresh(stdscr);
}

void TFMScreen::terminal_init() {
    ms_instance = this;

    initscr();
    raw();

    keypad(stdscr, TRUE);
    noecho();

    std::signal(SIGINT, ms_instance->handle_exit);
    std::signal(SIGWINCH, ms_instance->window_size_update);
}

void TFMScreen::terminal_destroy() {
    endwin();
    std::exit(0);
}