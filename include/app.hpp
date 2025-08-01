#ifndef APP_HPP
#define APP_HPP

#include "commandline.hpp"
#include "config.hpp"
#include "cursor.hpp"
#include "input.hpp"
#include "path.hpp"
#include "renderer.hpp"
#include "rows.hpp"
#include "screen.hpp"
#include "terminal.hpp"

class TFMApp {
   private:
    TFMConfig m_conf;
    TFMCommandline m_commandline;
    TFMRows m_rows;
    TFMScreen m_screen;
    TFMPathHandler m_path;
    TFMCursor m_cursor;
    TFMInput m_input;
    TFMRenderer m_renderer;

   public:
    TFMApp()
        : m_conf(),
          m_commandline(),
          m_rows(),
          m_screen(),
          m_path(),
          m_cursor(m_commandline, m_rows, m_screen),
          m_input(m_conf, m_cursor, m_rows, m_commandline),
          m_renderer(m_conf, m_rows, m_screen, m_path, m_cursor,
                     m_commandline) {
        m_conf.enable_command();
        m_conf.start_program();
    }
    ~TFMApp() {
        m_conf.end_program();
        m_conf.disable_command();
    }

    void run();
};

#endif