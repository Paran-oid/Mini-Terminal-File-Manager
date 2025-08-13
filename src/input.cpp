#include "input.hpp"

#include <ncurses.h>

#include <sstream>
#include <string>

#include "command_handler.hpp"
#include "command_history.hpp"
#include "command_line.hpp"
#include "config.hpp"
#include "core.hpp"
#include "cursor.hpp"
#include "path.hpp"
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
std::string TFMInput::extract_input_buf() {
    std::ostringstream buf;
    size_t current_index = m_command_line.get_row_index();

    buf << m_rows.at(current_index++).substr(m_command_line.get_size());

    while (current_index < m_rows.size()) {
        buf << m_rows.at(current_index++);
    }

    return buf.str();
}

void TFMInput::process() {
    int32_t c = getch();

    if (c == CTRL_KEY('q') || c == CTRL_KEY('Q')) m_config.end_program();

    TFMCursorCords cursor = m_cursor.get();

    size_t screen_row_off = m_screen.get_row_off();
    size_t screen_rows = m_screen.get_rows();

    size_t times = screen_rows;

    // TODO: make it show all matches if tab was clicked twice (used timeout)

    switch (c) {
        case KEY_BTAB:
        case '\t':
            this->match();
            break;

        case KEY_PPAGE:
        case KEY_NPAGE:
            if (c == KEY_PPAGE) {
                cursor.cy = screen_row_off;
            } else {
                cursor.cy = screen_rows + screen_row_off + 1;
                if (cursor.cy > m_rows.size()) {
                    cursor.cy = m_rows.size() - 1;
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
}

// TODO: make ctrl + arrow work (LATER)

void TFMInput::refresh() {
    if (m_rows.empty()) {
        return;
    }

    size_t cols = m_screen.get_cols();

    // handle underflow if any
    for (size_t i = 0; i < m_rows.size() - 1; i++) {
        std::string& row = m_rows.at(i);
        size_t len = row.length();

        if (len < cols && i + 1 < m_rows.size()) {
            std::string& next_row = m_rows.at(i + 1);
            size_t needed = cols - len;

            std::string to_add = next_row.substr(0, needed);
            row += to_add;
            next_row = next_row.substr(needed);

            if (next_row.empty()) {
                m_rows.pop_back();
            }
        }
    }

    // handle overflow if any
    for (size_t i = 0; i < m_rows.size(); i++) {
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
    std::string last_row = m_rows.back();
    TFMCursorCords cursor = m_cursor.get();

    auto current_rows = extract_current_rows();
    std::string cmd = extract_input_buf();

    m_command_history.add_previous(current_rows);
    m_rows.update(last_row, cursor.cy);

    m_config.enable_command();
    m_command_handler.process(cmd);
}

void TFMInput::append_char(char c) {
    const TFMCursorCords& cursor = m_cursor.get();

    size_t cursor_cx = cursor.cx;
    size_t cursor_cy = cursor.cy;

    std::vector<std::string> current_rows = extract_current_rows();
    std::string cmd = extract_input_buf();
    std::string& current_row = m_rows.at(cursor_cy);

    if (cursor_cx > current_row.size()) {
        current_row = current_row + (c);
    } else {
        current_row = current_row.substr(0, cursor_cx) + c +
                      current_row.substr(cursor_cx);
    }

    m_rows.update(current_row, cursor.cy);
    m_cursor.move(KEY_RIGHT);

    current_rows = extract_current_rows();
    m_command_history.set_last_entry(current_rows);

    this->refresh();
}

void TFMInput::match() {
    // TODO: make this work just like in linux terminal

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