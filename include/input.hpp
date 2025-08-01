#ifndef INPUT_HPP
#define INPUT_HPP

#include <cstdint>
#include <string>

struct Cursor;

class TFMConfig;
class TFMCursor;
class TFMRows;
class TFMCommandline;

class TFMInput {
   private:
    TFMConfig& m_conf;
    TFMCursor& m_cursor;
    TFMRows& m_rows;
    TFMCommandline& m_commandline;

   public:
    TFMInput(TFMConfig& conf, TFMCursor& cursor, TFMRows& rows,
             TFMCommandline& commandline)
        : m_conf{conf},
          m_cursor{cursor},
          m_rows{rows},
          m_commandline{commandline} {}
    ~TFMInput() = default;

    void remove(std::string& last_row, Cursor& cursor);
    void execute(const std::string& command);
    void process();
};

#endif