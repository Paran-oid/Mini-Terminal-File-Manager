#include "config.hpp"

#include <ncurses.h>

void TFMConfig::screen_dimensions_update() {
    getmaxyx(stdscr, m_screen.rows, m_screen.cols);
}

uint8_t TFMConfig::row_append(const std::string& data) {
    m_rows.push_back(data);
    return 0;
}

uint8_t TFMConfig::row_update(const std::string& data, int32_t at) {
    if (at < 0 || at >= m_rows.size()) {
        return 1;
    }

    m_rows[at] = data;
    return 0;
}

std::string TFMConfig::row_at(int32_t at) const { return m_rows[at]; }
size_t TFMConfig::rows_size() const { return m_rows.size(); }
uint8_t TFMConfig::is_cursor_at_last_row() {
    return m_cursor.cy == m_rows.size() - 1;
}

uint8_t TFMConfig::is_cursor_at_commandline() {
    return m_cursor.cy == m_commandline.row_index &&
           m_cursor.cx == m_commandline.data.length();
}
