#include "input.hpp"

#include <ncurses.h>

#include <string>

#include "config.hpp"
#include "core.hpp"
#include "cursor.hpp"
#include "rows.hpp"

uint8_t TFMInput::process() {
    int32_t c = getch();

    if (c == CTRL_KEY('q') || c == CTRL_KEY('Q')) return 2;

    Cursor cursor = m_cursor.get();
    std::string last_row = m_rows.at(cursor.cy);

    Cursor current_cursor_pos = m_cursor.get();

    switch (c) {
        case KEY_UP:
        case KEY_DOWN:
        case KEY_LEFT:
        case KEY_RIGHT:
            m_cursor.move(c);
            break;

        case '\r':
            // execute current command
            break;

        default:
            // ctrl key was pressed
            if (c >= 1 && c <= 26) {
            }

            last_row += c;
            m_rows.update(last_row, cursor.cy);

            m_cursor.move(KEY_RIGHT);
            break;
    }

    return 0;
}