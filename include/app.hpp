#pragma once

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
class FileManager;
}  // Namespace TFM

/**
 * @brief Central class that orchestrate all modules together
 *
 */
class TFMApp {
   private:
    TFMConfig m_config;
    TFM::FileManager m_file_manager;
    TFMCommandLine m_command_line;
    TFMScreen m_screen;
    TFMPathHandler m_path;
    TFMCommandHistory m_command_history;
    TFMRows m_rows;
    TFMCommandHandler m_command_handler;
    TFMCursor m_cursor;
    TFMRenderer m_renderer;
    TFMInput m_input;
    TFMDialog m_dialog;

   public:
    /**
     * @brief Construct a new TFMApp object
     *
     */
    TFMApp()
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
     * @brief Destroy the TFMApp object
     *
     */
    ~TFMApp() {
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
                                   TFMMessageType::M_COMMAND_LINE_TYPE);
        while (m_config.is_program_running()) {
            m_renderer.display();
            m_input.process();
        }

        m_screen.terminal_destroy();
    }
};
