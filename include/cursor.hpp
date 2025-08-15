#pragma once

#include <cstdint>

#include "command_line.hpp"
#include "rows.hpp"
#include "screen.hpp"

class TFMCommandLine;
class TFMRows;
class TFMScreen;
class TFMCommandHistory;

struct TFMCursorCords {
    size_t cx, cy;
};

class TFMCursor {
   private:
    TFMCursorCords m_app_cursor;

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
        m_app_cursor = {0, 0};
    }
    ~TFMCursor() = default;

    const TFMCursorCords& get() const { return m_app_cursor; }
    void set(size_t cx, size_t cy) { m_app_cursor = {cx, cy}; }

    void page_scroll(int32_t direction);
    void move(int32_t direction);
    void super_move(int32_t key);
    void update();

    bool is_cursor_at_last_row() {
        return m_app_cursor.cy == m_rows.size() - 1;
    }
    bool is_cursor_at_command_line() {
        return m_app_cursor.cy == m_command_line.get_row_index() &&
               m_app_cursor.cx == m_command_line.get_data().length();
        ;
    }
    bool is_cursor_at_end() {
        return m_app_cursor.cy ==
                   (m_rows.size() - m_screen.get_row_off() - 1) &&
               m_app_cursor.cx == m_rows.at(m_app_cursor.cy).size();
    }
};