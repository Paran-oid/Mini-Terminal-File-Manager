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

    // TODO: handle render cursor

   public:
    TFMCursor(TFMCommandline& commandline, TFMRows& rows, TFMScreen& screen)
        : m_commandline{commandline}, m_rows{rows}, m_screen{screen} {
        m_cursor = {0, 0, 0};
    }
    ~TFMCursor() = default;

    Cursor get() { return m_cursor; }
    void set(int32_t cx, int32_t cy) { m_cursor = {cx, convert_cx_rx(cx), cy}; }

    int32_t convert_cx_rx(int32_t cx);

    void move(int32_t direction);
    bool is_cursor_at_last_row();
    bool is_cursor_at_commandline();
};

#endif