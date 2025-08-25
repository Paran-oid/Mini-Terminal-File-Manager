#pragma once

#include <cstdint>
#include <sstream>

// responsible for drawing
class TFMConfig;
class TFMCursor;
class TFMRows;
class TFMScreen;
class TFMPathHandler;
class TFMCommandLine;

/**
 * @brief Provides rendering for all the app's features
 *
 */
class TFMRenderer {
   private:
    TFMConfig& m_config;
    TFMRows& m_rows;
    TFMScreen& m_screen;
    TFMPathHandler& m_path;
    TFMCursor& m_cursor;
    TFMCommandLine& m_command_line;

    std::ostringstream m_abuf;

   public:
    /**
     * @brief Construct a new TFMRenderer object
     *
     * @param config
     * @param rows
     * @param screen
     * @param path
     * @param cursor
     * @param command_line
     */
    TFMRenderer(TFMConfig& config, TFMRows& rows, TFMScreen& screen,
                TFMPathHandler& path, TFMCursor& cursor,
                TFMCommandLine& command_line)
        : m_config{config},
          m_rows{rows},
          m_screen{screen},
          m_path{path},
          m_cursor{cursor},
          m_command_line{command_line} {}
    ~TFMRenderer() = default;

    /**
     * @brief Scroll gets updated accordingly with the row offset
     *
     */
    void adjust_scroll();

    /**
     * @brief Displays the rows within current row interval (screen rows)
     *
     */
    void display();

    /**
     * @brief Draws each row accordinlgy
     *
     */
    void draw();
};
