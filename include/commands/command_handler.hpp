#pragma once

#include <unordered_map>

#include "command_executor.hpp"
#include "command_mapper.hpp"
#include "command_parser.hpp"

class TFMCommandParser;
class TFMCommandMapper;
class TFMCommandExecutor;
struct TFMCommand;
class TFMPathHandler;
class TFMRows;
class TFMScreen;
class TFMConfig;
class TFMDialog;

using fn = void (TFMCommandExecutor::*)(const TFMCommand&);

class TFMCommandHandler {
   private:
    TFMCommandParser m_parser;
    TFMCommandMapper m_mapper;
    TFMCommandExecutor m_executor;

   public:
    TFMCommandHandler(TFMPathHandler& path, TFMRows& rows, TFMScreen& screen,
                      TFMConfig& config, TFMCursor& cursor, TFMDialog& dialog)
        : m_parser(),
          m_mapper(),
          m_executor(path, rows, screen, config, cursor, dialog) {
        std::unordered_map<std::string, fn> commands_map{
            {"cd", &TFMCommandExecutor::cd_func},
            {"ls", &TFMCommandExecutor::ls_func},
            {"pwd", &TFMCommandExecutor::pwd_func},
            {"clear", &TFMCommandExecutor::clear_func},
            {"whoami", &TFMCommandExecutor::whoami_func},
            {"cp", &TFMCommandExecutor::cp_func},
            {"mkdir", &TFMCommandExecutor::mkdir_func},
            {"touch", &TFMCommandExecutor::touch_func},
            {"cat", &TFMCommandExecutor::cat_func},
            {"mv", &TFMCommandExecutor::mv_func}};

        for (auto& [name, func_ptr] : commands_map) {
            m_mapper.register_command(name,
                                      [this, func_ptr](const TFMCommand& cmd) {
                                          (m_executor.*func_ptr)(cmd);
                                      });
        }
    }

    ~TFMCommandHandler() = default;

    void process(const std::string& input);
};
