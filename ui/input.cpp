#include "input.hpp"

#include <ncurses.h>

int32_t terminal_read_key(void) {
    int32_t c = getch();
    return c;
}
int32_t terminal_process_input(void) {}