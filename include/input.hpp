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

class TFMInput {
   private:
    TFMConfig& m_conf;
    TFMCursor& m_cursor;
    TFMRows& m_rows;
    TFMCommandLine& m_command_line;
    TFMCommandHistory& m_command_history;
    TFMScreen& m_screen;

   public:
    TFMInput(TFMConfig& conf, TFMCursor& cursor, TFMRows& rows,
             TFMCommandLine& command_line, TFMCommandHistory& command_history,
             TFMScreen& screen)
        : m_conf{conf},
          m_cursor{cursor},
          m_rows{rows},
          m_command_line{command_line},
          m_command_history{command_history},
          m_screen{screen} {}
    ~TFMInput() = default;

    std::vector<std::string> extract_current_rows();
    std::string extract_command();

    void execute(const std::string& command);
    void process();
    void remove_char();
};

#endif