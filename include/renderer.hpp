#pragma once

#include <cstdint>
#include <sstream>

namespace TFM {

// responsible for drawing
class Config;
class Cursor;
class Rows;
class Screen;
class PathHandler;
class CommandLine;

/**
 * @brief Provides rendering for all the app's features
 *
 */
class Renderer {
   private:
    Config& m_config;
    Rows& m_rows;
    Screen& m_screen;
    PathHandler& m_path;
    Cursor& m_cursor;
    CommandLine& m_command_line;

    std::ostringstream m_abuf;

   public:
    /**
     * @brief Construct a new Renderer object
     *
     * @param config
     * @param rows
     * @param screen
     * @param path
     * @param cursor
     * @param command_line
     */
    Renderer(Config& config, Rows& rows, Screen& screen, PathHandler& path,
             Cursor& cursor, CommandLine& command_line)
        : m_config{config},
          m_rows{rows},
          m_screen{screen},
          m_path{path},
          m_cursor{cursor},
          m_command_line{command_line} {}

    /**
     * @brief Destroy the Renderer object
     *
     */
    ~Renderer() = default;

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

}  // namespace TFM
