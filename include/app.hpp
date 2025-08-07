#ifndef APP_HPP
#define APP_HPP

#include "command_handler.hpp"
#include "command_history.hpp"
#include "command_line.hpp"
#include "config.hpp"
#include "cursor.hpp"
#include "input.hpp"
#include "path.hpp"
#include "renderer.hpp"
#include "rows.hpp"
#include "screen.hpp"

class TFMApp {
   private:
    TFMConfig m_conf;
    TFMCommandLine m_command_line;
    TFMRows m_rows;
    TFMScreen m_screen;
    TFMPathHandler m_path;
    TFMCommandHistory m_command_history;
    TFMCommandHandler m_command_handler;
    TFMCursor m_cursor;
    TFMInput m_input;
    TFMRenderer m_renderer;

   public:
    TFMApp()
        : m_conf{},
          m_command_line{},
          m_rows{},
          m_screen{},
          m_path{},
          m_command_history{},
          m_command_handler{m_path, m_rows},
          m_cursor{m_command_line, m_rows, m_screen, m_command_history},
          m_input{m_conf,           m_cursor,          m_rows,
                  m_command_line,   m_command_history, m_screen,
                  m_command_handler},
          m_renderer{m_conf, m_rows,   m_screen,
                     m_path, m_cursor, m_command_line} {
        m_conf.start_program();
        m_conf.enable_command();
    }
    ~TFMApp() {
        m_conf.disable_command();
        m_conf.end_program();
    }

    void run();
};

#endif