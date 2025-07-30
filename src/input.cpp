#include "input.hpp"

#include <ncurses.h>

#include <string>

#include "config.hpp"
#include "core.hpp"

uint8_t TFMInput::cursor_move(int32_t direction) {
    Cursor cursor = m_conf.get_cursor();
    Screen screen = m_conf.get_screen();
    std::string current_row = m_conf.row_at(cursor.cy);

    switch (direction) {
        case KEY_RIGHT:
            if (cursor.cx >= screen.cols - 1) {
                if (m_conf.is_cursor_at_last_row()) {
                    m_conf.row_append("");
                }
                cursor.cy++;
                cursor.cx = 0;
            } else if (cursor.cx < current_row.length()) {
                cursor.cx++;
            }
            break;
        case KEY_LEFT:
            if (!m_conf.is_cursor_at_commandline() && cursor.cx != 0) {
                cursor.cx--;
            } else if (cursor.cx == 0) {
                cursor.cy--;
                current_row = m_conf.row_at(cursor.cy);
                cursor.cx = current_row.size() - 1;
            }
            break;
        // TODO: make this handle previous commands
        case KEY_UP:
            break;
        case KEY_DOWN:
            break;
        default:
            break;
    }

    m_conf.set_cursor(cursor);

    return 0;
}

uint8_t TFMInput::process() {
    int32_t c = getch();

    if (c == CTRL_KEY('q') || c == CTRL_KEY('Q')) return 2;

    Cursor cursor = m_conf.get_cursor();
    std::string last_row = m_conf.row_at(cursor.cy);

    Cursor current_cursor_pos = m_conf.get_cursor();

    switch (c) {
        case KEY_UP:
        case KEY_DOWN:
        case KEY_LEFT:
        case KEY_RIGHT:
            cursor_move(c);
            break;

        case '\r':
            // execute current command
            break;

        default:
            last_row += c;
            m_conf.row_update(last_row, cursor.cy);

            cursor_move(KEY_RIGHT);
            // TODO: make a move cursor function that handles cursor movement
            break;
    }

    return 0;
}