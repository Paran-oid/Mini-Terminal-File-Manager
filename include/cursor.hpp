#pragma once

#include <cstdint>

#include "command_line.hpp"
#include "rows.hpp"
#include "screen.hpp"

class TFMCommandLine;
class TFMRows;
class TFMScreen;
class TFMCommandHistory;

/**
 * @brief Holds coordinates of cursor
 *
 */
struct TFMCursorCords {
    size_t cx;  ///< cursor x coordinate (cols)
    size_t cy;  ///< cursor y coordinate (rows)
};

/**
 * @brief Manages everythin related to cursor
 *
 */
class TFMCursor {
   private:
    TFMCursorCords m_app_cursor;

    TFMCommandLine& m_command_line;
    TFMRows& m_rows;
    TFMScreen& m_screen;
    TFMCommandHistory& m_command_history;

   public:
    /**
     * @brief Construct a new TFMCursor object
     *
     * @param command_line
     * @param rows
     * @param screen
     * @param command_history
     */
    TFMCursor(TFMCommandLine& command_line, TFMRows& rows, TFMScreen& screen,
              TFMCommandHistory& command_history)
        : m_command_line{command_line},
          m_rows{rows},
          m_screen{screen},
          m_command_history{command_history} {
        m_app_cursor = {0, 0};
    }
    ~TFMCursor() = default;

    /**
     * @brief Gets the current cursor coordinates
     *
     * @return const TFMCursorCords&
     */
    const TFMCursorCords& get() const { return m_app_cursor; }

    /**
     * @brief Sets the current cursor coordinates
     *
     * @param cx
     * @param cy
     */
    void set(size_t cx, size_t cy) { m_app_cursor = {cx, cy}; }

    /**
     * @brief controls movement of cursor (arrows)
     *
     * @param direction
     */
    void move(int32_t direction);

    /**
     * @brief controls movement of cursor (ctrl-arrows)
     *
     * @param key
     */
    void super_move(int32_t key);

    /**
     * @brief Sets cursor to last possible position
     *
     */
    void move_to_end();

    /**
     * @brief Checks if cursor is at last row
     *
     * @return true
     * @return false
     */
    bool is_cursor_at_last_row() {
        return m_app_cursor.cy == m_rows.size() - 1;
    }

    /**
     * @brief Checks if cursor at command line
     *
     * @return true
     * @return false
     */
    bool is_cursor_at_command_line() {
        return m_app_cursor.cy == m_command_line.get_last_row_index() &&
               m_app_cursor.cx == m_command_line.get_data().length();
        ;
    }

    /**
     * @brief Checks if cursor at end
     *
     * @return true
     * @return false
     */
    bool is_cursor_at_end() {
        return m_app_cursor.cx >= m_rows.at(m_app_cursor.cy).size();
    }
};