#include "cursor.hpp"

#include <ncurses.h>

#include <stdexcept>

#include "command_history.hpp"
#include "renderer.hpp"
#include "screen.hpp"

void TFMCursor::page_scroll(int32_t direction) {
    if (direction == KEY_NPAGE) {
        if (m_cursor.cy < m_rows.size() - 1) {
            m_cursor.cy++;
        }
    } else if (direction == KEY_PPAGE) {
        if (m_cursor.cy > 0) {
            m_cursor.cy--;
        }
    } else {
        throw std::invalid_argument("invalid key passed");
    }
}

void TFMCursor::move(int32_t direction) {
    TFMScreenDetails screen = m_screen.get();

    const std::string& current_row = m_rows.at(m_cursor.cy);
    size_t m_command_line_row_index = m_command_line.get_row_index();

    std::vector<std::string> rows_temp;
    std::pair<size_t, size_t> tracked_data;

    switch (direction) {
        case KEY_RIGHT:
            if (m_cursor.cx >= screen.cols - 1) {
                if (is_cursor_at_last_row()) {
                    m_rows.append("");
                }
                m_cursor.cy++;
                m_cursor.cx = 0;
            } else if (m_cursor.cx < current_row.length()) {
                m_cursor.cx++;
            }
            break;
        case KEY_LEFT:
            if (!is_cursor_at_command_line() && m_cursor.cx > 0) {
                m_cursor.cx--;
            } else if (m_cursor.cx == 0) {
                m_cursor.cy--;
                m_cursor.cx = current_row.size() - 1;
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
                rows_temp = m_command_history.get_last_entry();
            }

            for (size_t i = 0; i < rows_temp.size(); i++) {
                tracked_data = {rows_temp[i].size(),
                                i + m_command_line_row_index};
                m_rows.at(tracked_data.second) = rows_temp[i];
            }
            this->set(tracked_data.first, tracked_data.second);

            break;
        default:
            throw std::invalid_argument(
                "TFMCursor: invalid cursor move instruction");
    }

    set(m_cursor.cx, m_cursor.cy);
}

void TFMCursor::update() {
    m_cursor.cx = m_rows.back().size();
    m_cursor.cy = m_rows.size() - 1;
}
