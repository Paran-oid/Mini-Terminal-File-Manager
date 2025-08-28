#pragma once

#include <functional>

#include "command_parser.hpp"

namespace TFM {
/// @brief importants required in CommandHandler
using command_func = std::function<void(const Command&)>;

struct Command;

class FileManager;
class PathHandler;
class Rows;
class Screen;
class Config;
class Cursor;
class Dialog;

enum CommandErrorCode {
    INVALID_COMMAND,
    UNAVAILABE_DIRECTORY_OR_FILE,
    UNAVAILABLE_DIRECTORY,
    MISSING_OPERAND,
    MISSING_FILE_OPERAND,
    MISSING_FILE_DESTINATION,
    MISSING_FILE_SOURCE,
    TARGET_DIRECTORY_NON_EXISTANT,
    DESTINATION_NOT_A_DIRECTORY,
    OVERWRITE_NON_DIR_WITH_DIR,
    FAILED_DIRECTORY_CREATION,
    FLAG_NOT_SPECIFIED,
    SAME_FILE_PASSED,
    EXPECTED_RECURSIVE_FLAG,
    FILESYSTEM_ERROR,
    UNKNOWN_ERROR
};

/**
 * @brief Executes passed commands
 *
 */
class CommandExecutor {
   private:
    PathHandler& m_path;
    Rows& m_rows;
    Screen& m_screen;
    Config& m_config;
    Cursor& m_cursor;
    Dialog& m_dialog;
    FileManager& m_file_manager;

   public:
    /**
     * @brief Construct a new CommandExecutor object
     *
     * @param path
     * @param rows
     * @param screen
     * @param config
     * @param cursor
     * @param dialog
     */
    CommandExecutor(PathHandler& path, Rows& rows, Screen& screen,
                    Config& config, Cursor& cursor, Dialog& dialog,
                    FileManager& file_manager)
        : m_path{path},
          m_rows{rows},
          m_screen(screen),
          m_config{config},
          m_cursor{cursor},
          m_dialog{dialog},
          m_file_manager{file_manager} {}

    /**
     * @brief Destroy the CommandExecutor object
     *
     */
    ~CommandExecutor() = default;

    /**
     * @brief Clears the terminal screen
     *
     * @param cmd Represents the "clear" command
     *
     * Usage:
     * @code
     * clear
     * @endcode
     */
    void clear_func(const Command& cmd);

    /**
     * @brief Changes the current directory
     *
     * @param cmd Represents the "cd" command
     *
     * Usage:
     * @code
     * cd <directory>
     * @endcode
     */
    void cd_func(const Command& cmd);

    /**
     * @brief Lists files and directories
     *
     * @param cmd Represents the "ls" command
     *
     * Usage:
     * @code
     * ls [options] [directory]
     * @endcode
     */
    void ls_func(const Command& cmd);

    /**
     * @brief Prints the current working directory
     *
     * @param cmd Represents the "pwd" command
     *
     * Usage:
     * @code
     * pwd
     * @endcode
     */
    void pwd_func(const Command& cmd);

    /**
     * @brief Displays the current user
     *
     * @param cmd Represents the "whoami" command
     *
     * Usage:
     * @code
     * whoami
     * @endcode
     */
    void whoami_func(const Command& cmd);

    /**
     * @brief Concatenates and displays file content
     *
     * @param cmd Represents the "cat" command
     *
     * Usage:
     * @code
     * cat <file1> [file2 ...]
     * @endcode
     */
    void cat_func(const Command& cmd);

    /**
     * @brief Copies files or directories
     *
     * @param cmd Represents the "cp" command
     *
     * Usage:
     * @code
     * cp <source> <destination>
     * @endcode
     */
    void cp_func(const Command& cmd);

    /**
     * @brief Moves or renames files or directories
     *
     * @param cmd Represents the "mv" command
     *
     * Usage:
     * @code
     * mv <source> <destination>
     * @endcode
     */
    void mv_func(const Command& cmd);

    /**
     * @brief Removes files or directories
     *
     * @param cmd Represents the "rm" command
     *
     * Usage:
     * @code
     * rm [options] <file1> [file2 ...]
     * @endcode
     */
    void rm_func(const Command& cmd);

    /**
     * @brief Creates new directories
     *
     * @param cmd Represents the "mkdir" command
     *
     * Usage:
     * @code
     * mkdir <directory_name>
     * @endcode
     */
    void mkdir_func(const Command& cmd);

    /**
     * @brief Creates empty files
     *
     * @param cmd Represents the "touch" command
     *
     * Usage:
     * @code
     * touch <file_name>
     * @endcode
     */
    void touch_func(const Command& cmd);

    /**
     * @brief Handles errors (doesn't crush the program whatsoever)
     *
     * @param cmd command in question
     * @param code error_code passed
     * @param data external data (required for some commands and others not)
     */
    void manage_error(const Command& cmd, CommandErrorCode code,
                      const std::vector<std::string> data = {});
};

}  // namespace TFM
