#include "renderer.hpp"

#include <ncurses.h>

#include "command_line.hpp"
#include "config.hpp"
#include "cursor.hpp"
#include "path.hpp"
#include "rows.hpp"
#include "screen.hpp"

void TFMRenderer::adjust_scroll() {
    const TFMCursorCords& cursor = m_cursor.get();

    size_t screen_row_off = m_screen.get_row_off();
    size_t screen_rows = m_screen.get_rows();

    if (cursor.cy < screen_row_off) {
        // screen_row_off = cursor.cy;
    } else if (cursor.cy >= screen_rows + screen_row_off) {
        screen_row_off = cursor.cy - screen_rows + 1;
    }

    m_screen.set_row_off(screen_row_off);
}

void TFMRenderer::display() {
    werase(stdscr);
    adjust_scroll();
    draw();

    printw("%s", m_abuf.str().c_str());

    const TFMCursorCords& cursor_current = m_cursor.get();
    int32_t calculated_cy =
        static_cast<int32_t>(cursor_current.cy - m_screen.get_row_off());
    int32_t calculated_cx = static_cast<int32_t>(cursor_current.cx);

    if (move(calculated_cy, calculated_cx) == -1) {
        throw std::out_of_range("invalid coordinates for cursor");
    }

    m_abuf.str("");
    m_abuf.clear();
}

void TFMRenderer::draw() {
    for (size_t i = m_screen.get_row_off(); i < m_rows.size(); i++) {
        const std::string& row = m_rows.at(i);
        m_abuf << row;
        if (row.size() != m_screen.get_cols()) {
            m_abuf << '\n';
        }
    }
}
