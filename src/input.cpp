#include "input.hpp"

#include <ncurses.h>

#include <sstream>
#include <string>

#include "command_handler.hpp"
#include "command_history.hpp"
#include "command_line.hpp"
#include "config.hpp"
#include "cursor.hpp"
#include "path.hpp"
#include "rows.hpp"
#include "screen.hpp"
#include "utils.hpp"

std::vector<std::string> TFMInput::extract_current_rows() {
    std::vector<std::string> res;
    size_t current_index = m_command_line.get_row_index();

    while (current_index < m_rows.size()) {
        res.push_back(m_rows.at(current_index++));
    }

    return res;
}

std::string TFMInput::extract_input_buf() {
    std::ostringstream buf;
    size_t current_index = m_command_line.get_row_index();

    buf << m_rows.at(current_index++).substr(m_command_line.get_size());

    while (current_index < m_rows.size()) {
        buf << m_rows.at(current_index++);
    }

    return buf.str();
}

void TFMInput::append_char(char c) {
    const TFMCursorCords& cursor = m_cursor.get();

    size_t cursor_cx = cursor.cx;
    size_t cursor_cy = cursor.cy;

    std::vector<std::string> current_rows = extract_current_rows();
    const std::string& cmd = extract_input_buf();
    std::string& current_row = m_rows.at(cursor_cy);

    if (cursor_cx > current_row.size()) {
        current_row = current_row + (c);
    } else {
        current_row = current_row.substr(0, cursor_cx) + c +
                      current_row.substr(cursor_cx);
    }

    m_cursor.move(KEY_RIGHT);

    current_rows = extract_current_rows();
    m_command_history.set_last_entry(current_rows);

    this->refresh();
}

void TFMInput::remove_char() {
    static bool callback = false;

    if (m_cursor.is_cursor_at_command_line()) {
        return;
    }

    // copy of cursor because we will need to get pos of cursors again later
    TFMCursorCords cursor = m_cursor.get();

    size_t cursor_cx = cursor.cx;
    size_t cursor_cy = cursor.cy;

    std::string& current_row = m_rows.at(cursor_cy);
    if (cursor_cx == 0) {
        m_cursor.move(KEY_LEFT);
        cursor = m_cursor.get();
        cursor_cx = cursor.cx;
        cursor_cy = cursor.cy;

        if (current_row.empty()) {
            m_rows.remove(cursor_cy + 1);
        }
        callback = true;
    } else {
        if (callback) {
            callback = false;
            current_row = current_row.substr(0, cursor_cx);
        } else {
            current_row = current_row.substr(0, cursor_cx - 1) +
                          current_row.substr(cursor_cx);
        }
        m_cursor.move(KEY_LEFT);
    }

    if (callback) {
        remove_char();
        m_cursor.move(KEY_RIGHT);
    }

    this->refresh();
}

void TFMInput::path_insert() {
    std::string formatted_curr_path = m_path.get_path().string() + ":~$ ";
    m_rows.append(formatted_curr_path);
    m_cursor.set(formatted_curr_path.length(), m_rows.size() - 1);

    const TFMCommandLineDetails new_command_line = {
        formatted_curr_path, m_rows.size() - 1, formatted_curr_path.size()};

    m_command_line.set(new_command_line);
}

void TFMInput::process() {
    static int32_t previous_c;
    int32_t c = getch();

    TFMCursorCords cursor = m_cursor.get();
    int32_t updated_row_off;

    if (c != KEY_PPAGE && c != KEY_NPAGE &&
        (previous_c == KEY_PPAGE || previous_c == KEY_NPAGE)) {
        m_cursor.move_to_end();
    }

    if (c == CTRL_KEY('q') || c == CTRL_KEY('Q')) {
        m_config.end_program();
    }

    switch (c) {
            /*
            !make it show all matches if tab was clicked twice (used
            !timeout)
            */

        case KEY_BTAB:
        case '\t':
            this->match();
            break;

        case KEY_PPAGE:
        case KEY_NPAGE:
            updated_row_off = static_cast<int32_t>(
                (m_screen.get_row_off() - m_screen.get_rows()));
            if (updated_row_off < 0) {
                updated_row_off = 0;
            }
            m_screen.set_row_off(static_cast<size_t>(updated_row_off));
            break;

        case KEY_UP:
        case KEY_DOWN:
        case KEY_LEFT:
        case KEY_RIGHT:
            m_cursor.move(c);
            break;

        case KEY_CTRL_RIGHT:
        case KEY_CTRL_LEFT:
            m_cursor.super_move(c);
            break;
        case '\n':
        case KEY_ENTER:
            this->enter();
            break;

        case '\r':
        case KEY_BACKSPACE:
        case KEY_DC:
            if (c == KEY_DC) {
                m_cursor.move(KEY_RIGHT);
            }
            return remove_char();

        case KEY_HOME:
            if (cursor.cy == m_command_line.get_row_index()) {
                m_cursor.set(m_command_line.get_size(), cursor.cy);
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

            this->append_char(static_cast<char>(c));
            break;
    }

    if (m_config.is_in_command()) {
        path_insert();
        m_config.disable_command();
    }
    previous_c = c;
}

void TFMInput::refresh() {
    if (m_rows.is_empty()) {
        return;
    }

    size_t cols = m_screen.get_cols();
    size_t command_line_index = m_command_line.get_row_index();

    // handle underflow if any
    for (size_t i = command_line_index; i < m_rows.size() - 1; i++) {
        std::string& row = m_rows.at(i);
        size_t len = row.length();

        if (len < cols && i + 1 < m_rows.size()) {
            std::string& next_row = m_rows.at(i + 1);
            size_t needed = cols - len;

            std::string to_add = next_row.substr(0, needed);
            row += to_add;
            next_row = next_row.substr(needed);

            if (next_row.empty()) {
                m_rows.remove_last();
            }
        }
    }

    // handle overflow if any
    for (size_t i = command_line_index; i < m_rows.size(); i++) {
        std::string& row = m_rows.at(i);
        size_t len = row.length();

        int32_t diff =
            std::abs(static_cast<int32_t>(cols) - static_cast<int32_t>(len));

        // user appended text to a full string
        if (diff < 0) {
            diff = -diff;
            std::string extra = row.substr(cols, static_cast<size_t>(diff));
            row = row.substr(0, cols);
            if (m_rows.size() < i + 1) {
                m_rows.append("");
            }
            std::string& last_row = m_rows.back();
            last_row = extra + last_row;
        }
    }
}

void TFMInput::enter() {
    if (m_cursor.get().cx == 0) {
        m_cursor.move(KEY_LEFT);
        m_rows.remove_last();
    }

    const std::vector<std::string>& current_rows = extract_current_rows();
    const std::string& cmd = extract_input_buf();
    m_command_history.add_previous(current_rows);

    m_config.enable_command();
    m_command_handler.process(cmd);
}

void TFMInput::match() {
    // TODO(LATER): make this work just like in linux terminal

    std::string input_buf = extract_input_buf();
    if (input_buf.empty()) {
        return;
    }

    std::string match = m_path.find_best_match(input_buf);

    if (match == input_buf) {
        return;
    }

    match = m_path.get_path().string() + ":~$ " + match;
    m_rows.remove_from(m_command_line.get_row_index());
    m_rows.append(match);
    m_cursor.update();
}
