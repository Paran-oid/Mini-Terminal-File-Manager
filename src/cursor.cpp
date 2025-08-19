#include "cursor.hpp"

#include <ncurses.h>

#include <stdexcept>

#include "command_history.hpp"
#include "renderer.hpp"
#include "utils.hpp"

void TFMCursor::move(int32_t direction) {
    TFMScreenDetails screen = m_screen.get();

    const std::string& current_row = m_rows.at(m_app_cursor.cy);
    size_t m_command_line_row_index = m_command_line.get_row_index();

    std::vector<std::string> rows_temp;

    // the size of the current row and its row index
    std::pair<size_t, size_t> row_info;

    switch (direction) {
        case KEY_RIGHT:
            if (m_app_cursor.cx >= screen.cols - 1) {
                if (is_cursor_at_last_row()) {
                    m_rows.append("");
                }
                m_app_cursor.cy++;
                m_app_cursor.cx = 0;
            } else if (m_app_cursor.cx < current_row.length()) {
                m_app_cursor.cx++;
            }
            break;
        case KEY_LEFT:
            if (!is_cursor_at_command_line() && m_app_cursor.cx > 0) {
                m_app_cursor.cx--;
            } else if (m_app_cursor.cx == 0) {
                m_app_cursor.cy--;
                m_app_cursor.cx = current_row.size() - 1;
            }
            break;
        case KEY_UP:
        case KEY_DOWN:
            if (direction == KEY_UP) {
                if (!m_command_history.has_previous()) {
                    return;
                }
                m_command_history.undo();
            } else {
                if (!m_command_history.has_upcoming()) {
                    return;
                }
                m_command_history.redo();
            }

            rows_temp = m_command_history.display_upcoming();
            if (rows_temp.empty()) {
                return;
            }

            if (rows_temp.empty()) {
                rows_temp = m_command_history.get_last_entry();
            }

            m_rows.remove_from(m_command_line.get_row_index());
            for (size_t i = 0; i < rows_temp.size(); i++) {
                row_info = {rows_temp[i].size(), i + m_command_line_row_index};
                m_rows.append(rows_temp[i]);
            }
            this->set(row_info.first, row_info.second);

            break;
        default:
            throw std::invalid_argument(
                "TFMCursor: invalid cursor move instruction");
    }

    set(m_app_cursor.cx, m_app_cursor.cy);
}

void TFMCursor::super_move(int32_t key) {
    char c = m_rows.at(m_app_cursor.cy)[m_app_cursor.cx];
    switch (key) {
        case KEY_CTRL_RIGHT:
            // move if current char is a separator
            c = m_rows.at(m_app_cursor.cy)[m_app_cursor.cx];
            if (is_seperator(c)) {
                this->move(KEY_RIGHT);
            }

            while (!this->is_cursor_at_end()) {
                c = m_rows.at(m_app_cursor.cy)[m_app_cursor.cx];
                if (is_seperator(c)) {
                    break;
                }
                this->move(KEY_RIGHT);
            }
            break;

        case KEY_CTRL_LEFT:
            // move if current char is a separator
            c = m_rows.at(m_app_cursor.cy)[m_app_cursor.cx];
            if (is_seperator(c)) {
                this->move(KEY_LEFT);
            }

            while (!this->is_cursor_at_command_line()) {
                c = m_rows.at(m_app_cursor.cy)[m_app_cursor.cx];
                if (is_seperator(c)) {
                    break;
                }
                this->move(KEY_LEFT);
            }
            break;
        default:
            throw std::runtime_error(
                "TFMCursor::super_move: invalid key passed");
            break;
    }
}

void TFMCursor::move_to_end() {
    while (!is_cursor_at_end()) {
        this->move(KEY_RIGHT);
    }
}

void TFMCursor::update() {
    m_app_cursor.cx = m_rows.back().size();
    m_app_cursor.cy = m_rows.size() - 1;
}
