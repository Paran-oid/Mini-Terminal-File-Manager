#pragma once

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

class TFMCommandHandler {
   private:
    TFMCommandParser m_parser;
    TFMCommandMapper m_mapper;
    TFMCommandExecutor m_executor;

   public:
    TFMCommandHandler(TFMPathHandler& path, TFMRows& rows, TFMScreen& screen,
                      TFMConfig& config)
        : m_parser(), m_mapper(), m_executor(path, rows, screen, config) {
        m_mapper.register_command(
            "cd", [this](const TFMCommand& cmd) { m_executor.cd_func(cmd); });
        m_mapper.register_command(
            "ls", [this](const TFMCommand& cmd) { m_executor.ls_func(cmd); });
        m_mapper.register_command(
            "pwd", [this](const TFMCommand& cmd) { m_executor.pwd_func(cmd); });
        m_mapper.register_command("clear", [this](const TFMCommand& cmd) {
            m_executor.clear_func(cmd);
        });
        m_mapper.register_command("whoami", [this](const TFMCommand& cmd) {
            m_executor.whoami_func(cmd);
        });
        m_mapper.register_command(
            "cp", [this](const TFMCommand& cmd) { m_executor.cp_func(cmd); });
        m_mapper.register_command("mkdir", [this](const TFMCommand& cmd) {
            m_executor.mkdir_func(cmd);
        });
        m_mapper.register_command("touch", [this](const TFMCommand& cmd) {
            m_executor.touch_func(cmd);
        });
        m_mapper.register_command(
            "cat", [this](const TFMCommand& cmd) { m_executor.cat_func(cmd); });
    }

    ~TFMCommandHandler() = default;

    void process(const std::string& input);
};
