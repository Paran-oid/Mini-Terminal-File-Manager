#include "input.hpp"

#include <ncurses.h>

#include <string>

#include "command_history.hpp"
#include "command_line.hpp"
#include "config.hpp"
#include "core.hpp"
#include "cursor.hpp"
#include "rows.hpp"
#include "screen.hpp"

std::vector<std::string> TFMInput::extract_current_rows() {
    std::vector<std::string> res;
    size_t current_index = m_command_line.get_row_index();

    while (current_index < m_rows.size()) {
        res.push_back(m_rows.at(current_index++));
    }

    return res;
}
std::string TFMInput::extract_command() { return {}; }

void TFMInput::execute(const std::string& command __attribute__((unused))) {
    return;
}

void TFMInput::process() {
    int32_t c = getch();

    if (c == CTRL_KEY('q') || c == CTRL_KEY('Q')) m_conf.end_program();

    Cursor cursor = m_cursor.get();
    std::string last_row = m_rows.at(static_cast<size_t>(cursor.cy));

    std::string command;
    std::vector<std::string> current_rows;

    int32_t screen_row_off = m_screen.get_row_off();
    int32_t screen_rows = m_screen.get_rows();

    int32_t times = screen_rows;

    switch (c) {
        case KEY_PPAGE:
        case KEY_NPAGE:
            if (c == KEY_PPAGE) {
                cursor.cy = screen_row_off;
            } else {
                cursor.cy = screen_rows + screen_row_off + 1;
                if (static_cast<size_t>(cursor.cy) > m_rows.size()) {
                    cursor.cy = static_cast<int32_t>(m_rows.size()) - 1;
                }
            }

            while (times--) {
                m_cursor.page_scroll(c);
            }
            m_screen.set_row_off(screen_row_off);
            break;

        case KEY_UP:
        case KEY_DOWN:
        case KEY_LEFT:
        case KEY_RIGHT:
            m_cursor.move(c);
            break;

        case '\n':
        case KEY_ENTER:
            current_rows = extract_current_rows();
            command = extract_command();
            m_command_history.add_previous(current_rows);

            m_conf.enable_command();
            execute(command);

            last_row += '\n';
            m_rows.update(last_row, static_cast<size_t>(cursor.cy));

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
            if (c >= 1 && c <= 26) {
                // ctrl key was pressed
                break;
            }

            if (c > 127) {
                // invalid char
                break;
            }

            last_row += static_cast<char>(c);
            m_rows.update(last_row, static_cast<size_t>(cursor.cy));

            current_rows = extract_current_rows();
            m_command_history.set_last_entry(current_rows);

            m_cursor.move(KEY_RIGHT);
            break;
    }
}

void TFMInput::remove_char() {
    static bool callback = false;

    Cursor cursor = m_cursor.get();
    std::string last_row = m_rows.back();

    if (m_cursor.is_cursor_at_command_line()) {
        return;
    }

    m_cursor.move(KEY_LEFT);

    if (last_row.empty()) {
        m_rows.pop_back();
        callback = true;
        last_row = m_rows.back();
    } else {
        last_row.pop_back();
    }

    cursor = m_cursor.get();

    m_rows.update(last_row, static_cast<size_t>(cursor.cy));

    if (callback) {
        callback = false;
        remove_char();
        m_cursor.move(KEY_RIGHT);
    }
}