#ifndef CURSOR_HPP
#define CURSOR_HPP

#include <cstdint>

class TFMCommandLine;
class TFMRows;
class TFMScreen;
class TFMCommandHistory;

struct Cursor {
    int32_t cx, cy;
};

class TFMCursor {
   private:
    Cursor m_cursor;

    TFMCommandLine& m_command_line;
    TFMRows& m_rows;
    TFMScreen& m_screen;
    TFMCommandHistory& m_command_history;

   public:
    TFMCursor(TFMCommandLine& command_line, TFMRows& rows, TFMScreen& screen,
              TFMCommandHistory& command_history)
        : m_command_line{command_line},
          m_rows{rows},
          m_screen{screen},
          m_command_history{command_history} {
        m_cursor = {0, 0};
    }
    ~TFMCursor() = default;

    Cursor get() { return m_cursor; }
    void set(int32_t cx, int32_t cy) { m_cursor = {cx, cy}; }

	void page_scroll(int32_t direction);
    void move(int32_t direction);
    bool is_cursor_at_last_row();
    bool is_cursor_at_command_line();
};

#endif