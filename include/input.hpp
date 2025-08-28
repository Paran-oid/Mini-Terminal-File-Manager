#pragma once

#include <cstdint>
#include <string>
#include <vector>

namespace TFM {

struct CursorCords;

class Config;
class Cursor;
class Rows;
class CommandLine;
class CommandHistory;
class Screen;
class CommandHandler;
class PathHandler;
class Renderer;

enum MessageType { M_COMMAND_LINE_TYPE, M_OTHER, MESSAGE_TYPE_COUNT };

/**
 * @brief Handles everything related to input (beside prompting)
 *
 */
class Input {
   private:
    Config& m_config;
    Cursor& m_cursor;
    Rows& m_rows;
    CommandLine& m_command_line;
    CommandHistory& m_command_history;
    Screen& m_screen;
    CommandHandler& m_command_handler;
    PathHandler& m_path;

    /**
     * @brief extracts current rows (command line content inclusive)
     *
     * @return std::vector<std::string>
     */
    std::vector<std::string> extract_current_rows();

    /**
     * @brief extracts input buff (command line content not inclusive)
     *
     * @return std::string
     */
    std::string extract_input_buf();

    /**
     * @brief Appends char to input buf at cursor position
     *
     * @param c
     */
    void append_char(char c);

    /**
     * @brief Removes char to input buf at cursor position
     *
     */
    void remove_char();

    /**
     * @brief Handles enter operation
     *
     */
    void enter();

    void commandline_insert(const std::string& content, MessageType type);

    friend class Dialog;
    friend class App;

   public:
    /**
     * @brief Construct a new Input object
     *
     * @param config
     * @param cursor
     * @param rows
     * @param command_line
     * @param command_history
     * @param screen
     * @param command_handler
     * @param path
     */
    Input(Config& config, Cursor& cursor, Rows& rows, CommandLine& command_line,
          CommandHistory& command_history, Screen& screen,
          CommandHandler& command_handler, PathHandler& path)
        : m_config{config},
          m_cursor{cursor},
          m_rows{rows},
          m_command_line{command_line},
          m_command_history{command_history},
          m_screen{screen},
          m_command_handler{command_handler},
          m_path{path} {}

    /**
     * @brief Destroy the Input object
     *
     */
    ~Input() = default;

    /**
     * @brief Processes user input
     *
     */
    void process();

    /**
     * @brief Inserts a new command
     *
     * @param content
     * @param type
     */
};

}  // namespace TFM
