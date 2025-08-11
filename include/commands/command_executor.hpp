#ifndef COMMAND_EXECUTOR_HPP
#define COMMAND_EXECUTOR_HPP

#include <functional>

#include "command_parser.hpp"

using command_func = std::function<void(const TFMCommand&)>;

struct TFMCommand;
class TFMPathHandler;
class TFMRows;
class TFMScreen;
class TFMConfig;

enum TFMCommandErrorCode { INVALID, UNAVAILABLE_DIRECTORY };

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
    void cd_func(const TFMCommand& args);
    void ls_func(const TFMCommand& args);
    void pwd_func(const TFMCommand& args);
    void whoami_func(const TFMCommand& args);

    void manage_error(const TFMCommand& args, TFMCommandErrorCode code);
};

#endif