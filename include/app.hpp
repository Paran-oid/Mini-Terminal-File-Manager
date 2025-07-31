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
    TFMCursor m_cursor;
    TFMInput m_input;
    TFMRenderer m_renderer;
    TFMScreen m_screen;
    TFMPathHandler m_path;

   public:
    TFMApp()
        : m_screen(),
          m_commandline(),
          m_rows(),
          m_cursor(m_commandline, m_rows, m_screen),
          m_input(m_conf, m_cursor, m_rows),
          m_renderer(m_conf, m_rows, m_screen, m_path, m_cursor,
                     m_commandline) {}
    ~TFMApp() {}

    void run();
};

#endif