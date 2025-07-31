#ifndef CURSOR_HPP
#define CURSOR_HPP

#include <cstdint>

class TFMCommandline;
class TFMRows;
class TFMScreen;

struct Cursor {
    int32_t cx, rx, cy;
};

class TFMCursor {
   private:
    Cursor m_cursor;

    TFMCommandline& m_commandline;
    TFMRows& m_rows;
    TFMScreen& m_screen;

   public:
    TFMCursor(TFMCommandline& commandline, TFMRows& rows, TFMScreen& screen)
        : m_commandline{commandline}, m_rows{rows}, m_screen{screen} {
        m_cursor = {0, 0, 0};
    }
    ~TFMCursor() = default;

    Cursor get() { return m_cursor; }
    void set(const Cursor& new_cursor) { m_cursor = new_cursor; }

    uint8_t move(int32_t direction);
    uint8_t is_cursor_at_last_row();
    uint8_t is_cursor_at_commandline();
};

#endif