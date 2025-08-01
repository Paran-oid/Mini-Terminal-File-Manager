#include "app.hpp"

#include "terminal.hpp"

void TFMApp::run() {
    while (m_conf.is_program_running()) {
        m_renderer.display();
        m_input.process();
    }
}