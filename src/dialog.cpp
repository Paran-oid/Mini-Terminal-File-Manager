#include "dialog.hpp"

#include <ncurses.h>

#include <sstream>

#include "command_line.hpp"
#include "config.hpp"
#include "input.hpp"
#include "renderer.hpp"
#include "rows.hpp"

std::string TFMDialog::receive(const std::string& message) {
    m_input.commandline_insert(message, TFMMessageType::M_OTHER);
    m_renderer.display();
    std::ostringstream out;
    int c;
    while (1) {
        c = getch();
        if (c == '\r' || c == '\n') {
            break;
        }

        if (std::isprint(c)) {
            m_input.append_char(static_cast<char>(c));
            out << static_cast<char>(c);
        }

        m_renderer.display();
    }
	
    m_config.enable_command();
    return out.str();
}
