#include "renderer.hpp"

#include <ncurses.h>

#include "commandline.hpp"
#include "config.hpp"
#include "cursor.hpp"
#include "path.hpp"
#include "rows.hpp"

void TFMRenderer::buf_append(const std::string& str) { m_abuf << str; }

void TFMRenderer::adjust_scroll() {}
void TFMRenderer::draw() {
    for (size_t i = 0; i < m_rows.size(); i++) {
        m_abuf << m_rows.at(i);
    }
    m_abuf << '\n';
}

void TFMRenderer::path_insert() {
    std::string formatted_curr_path = m_path.get().string() + ":~$ ";
    m_rows.append(formatted_curr_path);
    m_cursor.set(static_cast<int32_t>(formatted_curr_path.length()),
                 static_cast<int32_t>(m_rows.size() - 1));

    const Commandline new_commandline = {formatted_curr_path, m_rows.size() - 1,
                                         formatted_curr_path.size()};
    m_commandline.set(new_commandline);
}

void TFMRenderer::display() {
    clear();
    refresh();

    if (m_conf.is_in_command()) {
        path_insert();
        m_conf.disable_command();
    }

    adjust_scroll();
    draw();

    printw("%s", m_abuf.str().c_str());

    Cursor cursor_current = m_cursor.get();
    move(cursor_current.cy, cursor_current.cx);

    buf_clear();
}

void TFMRenderer::buf_clear() {
    m_abuf.str("");
    m_abuf.clear();
}