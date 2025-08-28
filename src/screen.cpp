#include "screen.hpp"

#include <ncurses.h>

#include <csignal>
#include <stdexcept>

#include "renderer.hpp"

TFM::Screen* TFM::Screen::ms_instance = nullptr;

void TFM::Screen::handle_exit(int32_t sig) {
    (void)sig;
    std::exit(0);
}

void TFM::Screen::window_size_update(int32_t sig) {
    (void)sig;
    if (TFM::Screen::ms_instance) {
        TFM::Screen::ms_instance->update_dimensions(sig);
    }
}

void TFM::Screen::update_dimensions(int32_t sig) {
    (void)sig;

    // update the internal structure of ncurses
    endwin();
    refresh();

    // get current rows and cols
    int32_t rows, cols;
    getmaxyx(stdscr, rows, cols);

    if (rows == -1 || cols == -1) {
        throw std::runtime_error(
            "TFM::Screen: error initializing screen dimensions");
    }

    m_app_screen.rows = static_cast<size_t>(rows);
    m_app_screen.cols = static_cast<size_t>(cols);

    wresize(stdscr, rows, cols);
    wrefresh(stdscr);
}

void TFM::Screen::terminal_init() {
    ms_instance = this;

    initscr();
    raw();

    keypad(stdscr, TRUE);
    noecho();

    std::signal(SIGINT, ms_instance->handle_exit);
    std::signal(SIGWINCH, ms_instance->window_size_update);
}

void TFM::Screen::terminal_destroy() {
    endwin();
    std::exit(0);
}