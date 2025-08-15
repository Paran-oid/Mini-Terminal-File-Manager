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

    void adjust_scroll();
    void display();
    void draw();
};
