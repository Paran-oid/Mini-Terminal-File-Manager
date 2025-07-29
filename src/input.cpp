#include "input.hpp"

#include <ncurses.h>

#include <string>

#include "config.hpp"
#include "core.hpp"

static void path_insert(TFMConfig& conf) {
    std::string formatted_curr_path = conf.get_current_path().string() + ":~$ ";
    conf.append_row(formatted_curr_path);
    conf.set_cursor({static_cast<int32_t>(formatted_curr_path.length()),
                     static_cast<int32_t>(conf.get_rows().size() - 1)});
}

uint8_t TFMInput::process() {
    if (!m_conf.get_started()) {
        path_insert(m_conf);
        m_conf.set_started(1);
    }

    char c = getch();

    if (c == CTRL_KEY('q') || c == CTRL_KEY('Q')) return 2;

    std::string& last_row = m_conf.get_rows()[m_conf.get_rows().size() - 1];
    switch (c) {
        case '\r':
            path_insert(m_conf);
            break;

        default:
            last_row += c;
            // TODO: make a move cursor function that handles cursor movement
            break;
    }

    return 0;
}