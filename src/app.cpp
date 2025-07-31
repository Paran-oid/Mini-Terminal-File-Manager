#include "app.hpp"

#include "terminal.hpp"

void TFMApp::run() {
    while (1) {
        m_renderer.display();
        if (m_input.process() == 2) {
            break;
        }
    }
}