#include "input.hpp"

#include <ncurses.h>

#include <string>

#include "commandline.hpp"
#include "config.hpp"
#include "core.hpp"
#include "cursor.hpp"
#include "rows.hpp"

void TFMInput::remove(std::string& last_row, Cursor& cursor) {
    if (m_cursor.is_cursor_at_commandline()) {
        return;
    }

    if (last_row.empty()) {
        // TODO: insert logic here
        m_rows.pop_back();
        last_row = m_rows.back();
    } else {
        last_row.pop_back();
    }

    m_cursor.move(KEY_LEFT);

    m_rows.update(last_row, static_cast<size_t>(cursor.cy));
}

void TFMInput::execute(const std::string& command) {}

void TFMInput::process() {
    int32_t c = getch();

    if (c == CTRL_KEY('q') || c == CTRL_KEY('Q')) m_conf.end_program();

    Cursor cursor = m_cursor.get();
    std::string last_row = m_rows.at(static_cast<size_t>(cursor.cy));

    switch (c) {
        case KEY_UP:
        case KEY_DOWN:
        case KEY_LEFT:
        case KEY_RIGHT:
            m_cursor.move(c);
            break;
        case '\n':
        case KEY_ENTER:
            // execute current command
            m_conf.enable_command();
            last_row += '\n';
            m_rows.update(last_row, static_cast<size_t>(cursor.cy));

            // TODO: we need to get all content of previous rows and turn them
            // TODO: into a one string command

            execute();
            break;

        case '\r':
        case KEY_BACKSPACE:
        case KEY_DC:
            if (c == KEY_DC) {
                m_cursor.move(KEY_RIGHT);
            }
            return remove(last_row, cursor);

        case KEY_HOME:
            if (static_cast<size_t>(cursor.cy) ==
                m_commandline.get_row_index()) {
                m_cursor.set(static_cast<int32_t>(m_commandline.get_size()),
                             cursor.cy);
            } else {
                m_cursor.set(0, cursor.cy);
            }
            break;

        default:
            // ctrl key was pressed
            if (c >= 1 && c <= 26) {
            }

            // invalid char
            if (c > 127) {
                break;
            }

            last_row += static_cast<char>(c);
            m_rows.update(last_row, static_cast<size_t>(cursor.cy));

            m_cursor.move(KEY_RIGHT);
            break;
    }
}