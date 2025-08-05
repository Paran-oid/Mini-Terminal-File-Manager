#include "renderer.hpp"

#include <ncurses.h>

#include "command_line.hpp"
#include "config.hpp"
#include "cursor.hpp"
#include "path.hpp"
#include "rows.hpp"
#include "screen.hpp"

void TFMRenderer::buf_append(const std::string& str) { m_abuf << str; }

void TFMRenderer::adjust_scroll() {
    Cursor cursor = m_cursor.get();

    int32_t screen_row_off = m_screen.get_row_off();
    int32_t screen_rows = m_screen.get_rows();

    if (cursor.cy < screen_row_off) {
        screen_row_off = cursor.cy;
    } else if (cursor.cy >= screen_rows + screen_row_off) {
        screen_row_off = cursor.cy - screen_rows + 1;
    }

    m_screen.set_row_off(screen_row_off);
}
void TFMRenderer::draw() {
    for (size_t i = static_cast<size_t>(m_screen.get_row_off());
         i < m_rows.size(); i++) {
        m_abuf << m_rows.at(i);
    }
}

void TFMRenderer::path_insert() {
    std::string formatted_curr_path = m_path.get().string() + ":~$ ";
    m_rows.append(formatted_curr_path);
    m_cursor.set(static_cast<int32_t>(formatted_curr_path.length()),
                 static_cast<int32_t>(m_rows.size() - 1));

    const command_line new_command_line = {
        formatted_curr_path, m_rows.size() - 1, formatted_curr_path.size()};
    m_command_line.set(new_command_line);
}

void TFMRenderer::display() {
    werase(stdscr);

    if (m_conf.is_in_command()) {
        path_insert();
        m_conf.disable_command();
    }

    adjust_scroll();
    draw();

    std::string temp = m_abuf.str().c_str();
    printw("%s", m_abuf.str().c_str());

    Cursor cursor_current = m_cursor.get();
    if (move(cursor_current.cy - m_screen.get_row_off(), cursor_current.cx) ==
        -1) {
        throw std::out_of_range("invalid coordinates for cursor");
    }

    buf_clear();
}

void TFMRenderer::buf_clear() {
    m_abuf.str("");
    m_abuf.clear();
}