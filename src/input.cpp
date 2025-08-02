#include "input.hpp"

#include <ncurses.h>

#include <string>

#include "command_history.hpp"
#include "command_line.hpp"
#include "config.hpp"
#include "core.hpp"
#include "cursor.hpp"
#include "rows.hpp"

void TFMInput::remove_char() {
    Cursor cursor = m_cursor.get();
    std::string last_row = m_rows.back();
    if (m_cursor.is_cursor_at_command_line()) {
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
std::string TFMInput::extract_command() {
    size_t current_index = m_command_line.get_row_index();
    std::ostringstream res_stream;

    res_stream << m_rows.at(current_index++).substr(m_command_line.get_size());

    while (current_index < m_rows.size()) {
        res_stream << m_rows.at(current_index++);
    }

    return res_stream.str();
}

void TFMInput::execute(const std::string& command __attribute__((unused))) {
    return;
}

void TFMInput::process() {
    int32_t c = getch();

    if (c == CTRL_KEY('q') || c == CTRL_KEY('Q')) m_conf.end_program();

    Cursor cursor = m_cursor.get();
    std::string last_row = m_rows.at(static_cast<size_t>(cursor.cy));
    std::string command_extracted;

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

            command_extracted = extract_command();
            m_command_history.add_previous(command_extracted);

            execute(command_extracted);
            break;

        case '\r':
        case KEY_BACKSPACE:
        case KEY_DC:
            if (c == KEY_DC) {
                m_cursor.move(KEY_RIGHT);
            }
            return remove_char();

        case KEY_HOME:
            if (static_cast<size_t>(cursor.cy) ==
                m_command_line.get_row_index()) {
                m_cursor.set(static_cast<int32_t>(m_command_line.get_size()),
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