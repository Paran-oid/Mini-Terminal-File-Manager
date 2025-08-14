#pragma once

#include <cstdint>

#include "command_line.hpp"
#include "rows.hpp"

class TFMCommandLine;
class TFMRows;
class TFMScreen;
class TFMCommandHistory;

struct TFMCursorCords {
    size_t cx, cy;
};

class TFMCursor {
   private:
    TFMCursorCords m_cursor;

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

    const TFMCursorCords& get() const { return m_cursor; }
    void set(size_t cx, size_t cy) { m_cursor = {cx, cy}; }

    void page_scroll(int32_t direction);
    void move(int32_t direction);
    void update();

    bool is_cursor_at_last_row() { return m_cursor.cy == m_rows.size() - 1; }
    bool is_cursor_at_command_line() {
        return m_cursor.cy == m_command_line.get_row_index() &&
               m_cursor.cx == m_command_line.get_data().length();
        ;
    }
};