#include "cursor.hpp"

#include <ncurses.h>

#include <stdexcept>

#include "command_history.hpp"
#include "command_line.hpp"
#include "renderer.hpp"
#include "rows.hpp"
#include "screen.hpp"

int32_t TFMCursor::convert_cx_rx(int32_t cx) { return cx; }

bool TFMCursor::is_cursor_at_last_row() {
    return m_cursor.cy == static_cast<int32_t>(m_rows.size()) - 1;
}

bool TFMCursor::is_cursor_at_command_line() {
    return static_cast<size_t>(m_cursor.cy) == m_command_line.get_row_index() &&
           static_cast<size_t>(m_cursor.cx) ==
               m_command_line.get_data().length();
}

void TFMCursor::move(int32_t direction) {
    Screen screen = m_screen.get();
    std::string current_row = m_rows.at(static_cast<size_t>(m_cursor.cy));
    std::string content;

    switch (direction) {
        case KEY_RIGHT:
            if (m_cursor.cx >= screen.cols - 1) {
                if (is_cursor_at_last_row()) {
                    m_rows.append("");
                }
                m_cursor.cy++;
                m_cursor.cx = 0;
            } else if (static_cast<size_t>(m_cursor.cx) <
                       current_row.length()) {
                m_cursor.cx++;
            }
            break;
        case KEY_LEFT:
            if (!is_cursor_at_command_line() && m_cursor.cx != 0) {
                m_cursor.cx--;
            } else if (m_cursor.cx == 0) {
                m_cursor.cy--;
                current_row = m_rows.at(static_cast<size_t>(m_cursor.cy));
                m_cursor.cx = static_cast<int32_t>(current_row.size()) - 1;
            }
            break;
        // TODO: make this handle previous commands
        case KEY_UP:
            // TODO: make commands get formatted first into rows and then add
            // TODO: each of them

            if (!m_command_history.has_previous()) {
                return;
            }

            m_command_history.undo();

            break;
        case KEY_DOWN:
            m_command_history.redo();
            content = m_command_history.display_previous();
            m_rows.format_string_to_rows(content);

            break;
        default:
            throw std::invalid_argument(
                "TFMCursor: invalid cursor move instruction");
    }

    // updates the cursor
    set(m_cursor.cx, m_cursor.cy);
}
