#include "cursor.hpp"

#include <ncurses.h>

#include "commandline.hpp"
#include "rows.hpp"
#include "screen.hpp"

uint8_t TFMCursor::is_cursor_at_last_row() {
    return m_cursor.cy == m_rows.size() - 1;
}

uint8_t TFMCursor::is_cursor_at_commandline() {
    return m_cursor.cy == m_commandline.get_row_index() &&
           m_cursor.cx == m_commandline.get_data().length();
}

uint8_t TFMCursor::move(int32_t direction) {
    Screen screen = m_screen.get();
    std::string current_row = m_rows.at(m_cursor.cy);

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
            if (!is_cursor_at_commandline() && m_cursor.cx != 0) {
                m_cursor.cx--;
            } else if (m_cursor.cx == 0) {
                m_cursor.cy--;
                current_row = m_rows.at(m_cursor.cy);
                m_cursor.cx = current_row.size() - 1;
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

    // updates the cursor
    set(m_cursor);

    return 0;
}
