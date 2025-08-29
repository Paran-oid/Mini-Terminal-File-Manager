#pragma once

#include <filesystem>

#include "command_handler.hpp"
#include "command_history.hpp"
#include "command_line.hpp"
#include "config.hpp"
#include "cursor.hpp"
#include "dialog.hpp"
#include "file.hpp"
#include "input.hpp"
#include "path.hpp"
#include "renderer.hpp"
#include "rows.hpp"
#include "screen.hpp"

namespace TFM {

/**
 * @brief Central class that orchestrate all modules together
 *
 */
class App {
   private:
    Config m_config;
    FileManager m_file_manager;
    CommandLine m_command_line;
    Screen m_screen;
    PathHandler m_path;
    CommandHistory m_command_history;
    Rows m_rows;
    CommandHandler m_command_handler;
    Cursor m_cursor;
    Renderer m_renderer;
    Input m_input;
    Dialog m_dialog;

   public:
    /**
     * @brief Construct a new TFMApp object
     *
     */
    App()
        : m_config{},
          m_file_manager{},
          m_command_line{},
          m_screen{},
          m_path{},
          m_command_history{},
          m_rows{m_screen},
          m_command_handler{m_path,   m_rows,   m_screen,      m_config,
                            m_cursor, m_dialog, m_file_manager},
          m_cursor{m_command_line, m_rows, m_screen, m_command_history},

          m_renderer{m_config, m_rows,   m_screen,
                     m_path,   m_cursor, m_command_line},
          m_input{m_config,
                  m_cursor,
                  m_rows,
                  m_command_line,
                  m_command_history,
                  m_screen,
                  m_command_handler,
                  m_path},
          m_dialog{m_renderer, m_config, m_input} {
        m_config.start_program();
        m_config.disable_command();
    }

    /**
     * @brief Destroy the App object
     *
     */
    ~App() {
        m_config.disable_command();
        m_config.end_program();
    }

    /**
     * @brief Executes the program
     *
     */
    void run() {
        m_screen.terminal_init();

        m_input.commandline_insert(m_path.get_path().string(),
                                   MessageType::M_COMMAND_LINE_TYPE);
        while (m_config.is_program_running()) {
            m_renderer.display();
            m_input.process();
        }

        m_screen.terminal_destroy();
    }
};

}  // namespace TFM
