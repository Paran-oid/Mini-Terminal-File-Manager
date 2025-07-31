#ifndef INPUT_HPP
#define INPUT_HPP

#include <cstdint>

class TFMConfig;
class TFMCursor;
class TFMRows;

class TFMInput {
   private:
    TFMConfig& m_conf;
    TFMCursor& m_cursor;
    TFMRows& m_rows;

   public:
    TFMInput(TFMConfig& conf, TFMCursor& cursor, TFMRows& rows)
        : m_conf{conf}, m_cursor{cursor}, m_rows{rows} {}
    ~TFMInput() = default;

    uint8_t process();
};

#endif