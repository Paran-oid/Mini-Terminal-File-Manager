#pragma once

#include <cstdint>
#include <string>
#include <vector>

struct TFMCursorCords;

class TFMConfig;
class TFMCursor;
class TFMRows;
class TFMCommandLine;
class TFMCommandHistory;
class TFMScreen;
class TFMCommandHandler;
class TFMPathHandler;
class TFMRenderer;

class TFMInput {
   private:
    TFMConfig& m_config;
    TFMCursor& m_cursor;
    TFMRows& m_rows;
    TFMCommandLine& m_command_line;
    TFMCommandHistory& m_command_history;
    TFMScreen& m_screen;
    TFMCommandHandler& m_command_handler;
    TFMPathHandler& m_path;
    TFMRenderer& m_renderer;

   public:
    TFMInput(TFMConfig& config, TFMCursor& cursor, TFMRows& rows,
             TFMCommandLine& command_line, TFMCommandHistory& command_history,
             TFMScreen& screen, TFMCommandHandler& command_handler,
             TFMPathHandler& path, TFMRenderer& renderer)
        : m_config{config},
          m_cursor{cursor},
          m_rows{rows},
          m_command_line{command_line},
          m_command_history{command_history},
          m_screen{screen},
          m_command_handler{command_handler},
          m_path{path},
          m_renderer{renderer} {}
    ~TFMInput() = default;

    std::vector<std::string> extract_current_rows();
    std::string extract_input_buf();

    void append_char(char c);
    void remove_char();
    void path_insert();
    void process();
    void refresh();
    void enter();
    void match();
};
