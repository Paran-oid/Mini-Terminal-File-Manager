#include "cursor.hpp"

#include <ncurses.h>

#include <stdexcept>

#include "commandline.hpp"
#include "rows.hpp"
#include "screen.hpp"

int32_t TFMCursor::convert_cx_rx(int32_t cx) { return cx; }

bool TFMCursor::is_cursor_at_last_row() {
    return m_cursor.cy == static_cast<int32_t>(m_rows.size()) - 1;
}

bool TFMCursor::is_cursor_at_commandline() {
    return static_cast<size_t>(m_cursor.cy) == m_commandline.get_row_index() &&
           static_cast<size_t>(m_cursor.cx) ==
               m_commandline.get_data().length();
}

void TFMCursor::move(int32_t direction) {
    Screen screen = m_screen.get();
    std::string current_row = m_rows.at(static_cast<size_t>(m_cursor.cy));

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
            if (!is_cursor_at_commandline() && m_cursor.cx != 0) {
                m_cursor.cx--;
            } else if (m_cursor.cx == 0) {
                m_cursor.cy--;
                current_row = m_rows.at(static_cast<size_t>(m_cursor.cy));
                m_cursor.cx = static_cast<int32_t>(current_row.size()) - 1;
            }
            break;
        // TODO: make this handle previous commands
        case KEY_UP:
            break;
        case KEY_DOWN:
            break;
        default:
            throw std::invalid_argument(
                "TFMCursor: invalid cursor move instruction");
    }

    // updates the cursor
    set(m_cursor.cx, m_cursor.cy);
}
