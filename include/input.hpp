#ifndef INPUT_HPP
#define INPUT_HPP

#include <cstdint>
#include <string>
#include <vector>

struct Cursor;

class TFMConfig;
class TFMCursor;
class TFMRows;
class TFMCommandLine;
class TFMCommandHistory;
class TFMScreen;
class TFMCommandHandler;
class TFMPathHandler;

class TFMInput {
   private:
    TFMConfig& m_conf;
    TFMCursor& m_cursor;
    TFMRows& m_rows;
    TFMCommandLine& m_command_line;
    TFMCommandHistory& m_command_history;
    TFMScreen& m_screen;
    TFMCommandHandler& m_command_handler;
    TFMPathHandler& m_path;

   public:
    TFMInput(TFMConfig& conf, TFMCursor& cursor, TFMRows& rows,
             TFMCommandLine& command_line, TFMCommandHistory& command_history,
             TFMScreen& screen, TFMCommandHandler& command_handler,
             TFMPathHandler& path)
        : m_conf{conf},
          m_cursor{cursor},
          m_rows{rows},
          m_command_line{command_line},
          m_command_history{command_history},
          m_screen{screen},
          m_command_handler{command_handler},
          m_path{path} {}
    ~TFMInput() = default;

    std::vector<std::string> extract_current_rows();
    std::string extract_command();

    void append_char(int32_t c);
    void remove_char();
    void process();
    void enter();
    void match();
};

#endif