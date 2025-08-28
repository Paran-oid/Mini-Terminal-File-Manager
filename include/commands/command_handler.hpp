#pragma once

#include <unordered_map>

#include "command_executor.hpp"
#include "command_mapper.hpp"
#include "command_parser.hpp"

namespace TFM {

class FileManager;
class CommandParser;
class CommandMapper;
class CommandExecutor;
struct Command;
class PathHandler;
class Rows;
class Screen;
class Config;
class Dialog;

/// @brief fn defined to be able to map each command (string) to function (fn)
using fn = void (CommandExecutor::*)(const Command&);

/**
 * @brief Orchestrates command componments (parser, mapper, executor)
 *
 */
class CommandHandler {
   private:
    CommandParser m_parser;
    CommandMapper m_mapper;
    CommandExecutor m_executor;

   public:
    /**
     * @brief Construct a new CommandHandler object and maps each command
     * with it's function
     *
     * @param path
     * @param rows
     * @param screen
     * @param config
     * @param cursor
     * @param dialog
     */
    CommandHandler(PathHandler& path, Rows& rows, Screen& screen,
                   Config& config, Cursor& cursor, Dialog& dialog,
                   FileManager& file_manager)
        : m_parser(),
          m_mapper(),
          m_executor(path, rows, screen, config, cursor, dialog, file_manager) {
        std::unordered_map<std::string, fn> commands_map{
            {"cd", &CommandExecutor::cd_func},
            {"ls", &CommandExecutor::ls_func},
            {"pwd", &CommandExecutor::pwd_func},
            {"clear", &CommandExecutor::clear_func},
            {"whoami", &CommandExecutor::whoami_func},
            {"cp", &CommandExecutor::cp_func},
            {"mkdir", &CommandExecutor::mkdir_func},
            {"touch", &CommandExecutor::touch_func},
            {"cat", &CommandExecutor::cat_func},
            {"mv", &CommandExecutor::mv_func},
            {"rm", &CommandExecutor::rm_func}};

        for (auto& [name, func_ptr] : commands_map) {
            m_mapper.register_command(name,
                                      [this, func_ptr](const Command& cmd) {
                                          (m_executor.*func_ptr)(cmd);
                                      });
        }
    }

    /**
     * @brief Destroy the CommandHandler object
     *
     */
    ~CommandHandler() = default;

    /**
     * @brief Processes entered command by user
     *
     * @param input
     */
    void process(const std::string& input);
};

}  // namespace TFM
