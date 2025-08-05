#include "app.hpp"

void TFMApp::run() {
    m_screen.terminal_init();

    while (m_conf.is_program_running()) {
        m_renderer.display();
        m_input.process();
    }

    m_screen.terminal_destroy();
}