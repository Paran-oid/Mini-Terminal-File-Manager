#pragma once

#include <functional>

#include "command_parser.hpp"

/// @brief importants required in TFMCommandHandler
using command_func = std::function<void(const TFMCommand&)>;

struct TFMCommand;
class TFMPathHandler;
class TFMRows;
class TFMScreen;
class TFMConfig;
class TFMCursor;
class TFMDialog;

enum TFMCommandErrorCode {
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
    NONE
};

/**
 * @brief Executes passed commands
 *
 */
class TFMCommandExecutor {
   private:
    TFMPathHandler& m_path;
    TFMRows& m_rows;
    TFMScreen& m_screen;
    TFMConfig& m_config;
    TFMCursor& m_cursor;
    TFMDialog& m_dialog;

   public:
    /**
     * @brief Construct a new TFMCommandExecutor object
     *
     * @param path
     * @param rows
     * @param screen
     * @param config
     * @param cursor
     * @param dialog
     */
    TFMCommandExecutor(TFMPathHandler& path, TFMRows& rows, TFMScreen& screen,
                       TFMConfig& config, TFMCursor& cursor, TFMDialog& dialog)
        : m_path{path},
          m_rows{rows},
          m_screen(screen),
          m_config{config},
          m_cursor{cursor},
          m_dialog{dialog} {}

    /**
     * @brief Destroy the TFMCommandExecutor object
     *
     */
    ~TFMCommandExecutor() = default;

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
    void clear_func(const TFMCommand& cmd);

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
    void cd_func(const TFMCommand& cmd);

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
    void ls_func(const TFMCommand& cmd);

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
    void pwd_func(const TFMCommand& cmd);

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
    void whoami_func(const TFMCommand& cmd);

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
    void cat_func(const TFMCommand& cmd);

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
    void cp_func(const TFMCommand& cmd);

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
    void mv_func(const TFMCommand& cmd);

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
    void rm_func(const TFMCommand& cmd);

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
    void mkdir_func(const TFMCommand& cmd);

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
    void touch_func(const TFMCommand& cmd);

    /**
     * @brief Handles errors (doesn't crush the program whatsoever)
     *
     * @param cmd command in question
     * @param code error_code passed
     * @param data external data (required for some commands and others not)
     */
    void manage_error(const TFMCommand& cmd, TFMCommandErrorCode code,
                      const std::vector<std::string> data = {});
};
