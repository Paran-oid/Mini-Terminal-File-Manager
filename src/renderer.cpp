#include "renderer.hpp"

#include <ncurses.h>

#include "config.hpp"

void TFMRenderer::buf_append(const std::string& str) { m_abuf << str; }

uint8_t TFMRenderer::adjust_scroll() { return 0; }
uint8_t TFMRenderer::draw() {
    for (size_t i = 0; i < m_conf.rows_size(); i++) {
        m_abuf << m_conf.row_at(i);
    }
    m_abuf << '\n';
    return 0;
}

static void path_insert(TFMConfig& conf) {
    std::string formatted_curr_path = conf.get_current_path().string() + ":~$ ";
    conf.row_append(formatted_curr_path);
    conf.set_cursor({static_cast<int32_t>(formatted_curr_path.length()),
                     static_cast<int32_t>(conf.rows_size() - 1)});
    conf.set_commandline({formatted_curr_path, conf.rows_size() - 1,
                          formatted_curr_path.size()});
}

uint8_t TFMRenderer::display() {
    clear();
    refresh();

    if (!m_conf.get_started()) {
        path_insert(m_conf);
        m_conf.set_started(1);
    }

    adjust_scroll();
    draw();

    printw("%s", m_abuf.str().c_str());

    Cursor cursor_current = m_conf.get_cursor();
    move(cursor_current.cy, cursor_current.cx);

    m_abuf.str("");
    m_abuf.clear();
    return 0;
}