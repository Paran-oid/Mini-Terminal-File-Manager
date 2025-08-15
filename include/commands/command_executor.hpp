#pragma once

#include <functional>

#include "command_parser.hpp"

using command_func = std::function<void(const TFMCommand&)>;

struct TFMCommand;
class TFMPathHandler;
class TFMRows;
class TFMScreen;
class TFMConfig;

enum TFMCommandErrorCode {
    INVALID_COMMAND,
    UNAVAILABLE_DIRECTORY,
    MISSING_OPERAND,
    MISSING_FILE_OPERAND,
    MISSING_FILE_DESTINATION,
    FAILED_DIRECTORY_CREATION,
    NONE
};

class TFMCommandExecutor {
   private:
    TFMPathHandler& m_path;
    TFMRows& m_rows;
    TFMScreen& m_screen;
    TFMConfig& m_config;

   public:
    TFMCommandExecutor(TFMPathHandler& path, TFMRows& rows, TFMScreen& screen,
                       TFMConfig& config)
        : m_path{path}, m_rows{rows}, m_screen(screen), m_config{config} {}
    ~TFMCommandExecutor() = default;

    void clear_func(const TFMCommand& cmd);
    void cd_func(const TFMCommand& cmd);
    void ls_func(const TFMCommand& cmd);
    void pwd_func(const TFMCommand& cmd);
    void whoami_func(const TFMCommand& cmd);
    void cat_func(const TFMCommand& cmd);

    void cp_func(const TFMCommand& cmd);
    void mkdir_func(const TFMCommand& cmd);
    void touch_func(const TFMCommand& cmd);

    void manage_error(const TFMCommand& cmd, TFMCommandErrorCode code,
                      std::string data = "");
};
