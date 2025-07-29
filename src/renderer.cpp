#include "renderer.hpp"

#include <ncurses.h>

#include "config.hpp"

void TFMRenderer::buf_append(const std::string& str) { m_abuf << str; }

uint8_t TFMRenderer::adjust_scroll() { return 0; }
uint8_t TFMRenderer::draw() {
    for (const auto& row_content : m_conf.get_rows()) {
        m_abuf << row_content << "\n";
    }
    return 0;
}
uint8_t TFMRenderer::display() {
    clear();
    refresh();

    adjust_scroll();
    draw();

    printw("%s", m_abuf.str().c_str());

    Cursor cursor_current = m_conf.get_cursor();
    move(cursor_current.cy, cursor_current.cx);

    m_abuf.str("");
    m_abuf.clear();
    return 0;
}