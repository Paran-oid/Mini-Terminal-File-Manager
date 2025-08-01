#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <cstdint>
#include <sstream>

// responsible for drawing
class TFMConfig;
class TFMCursor;
class TFMRows;
class TFMScreen;
class TFMPathHandler;
class TFMCommandline;

class TFMRenderer {
   private:
    TFMConfig& m_conf;
    TFMRows& m_rows;
    TFMScreen& m_screen;
    TFMPathHandler& m_path;
    TFMCursor& m_cursor;
    TFMCommandline& m_commandline;

    std::ostringstream m_abuf;

   public:
    TFMRenderer(TFMConfig& conf, TFMRows& rows, TFMScreen& screen,
                TFMPathHandler& path, TFMCursor& cursor,
                TFMCommandline& commandline)
        : m_conf{conf},
          m_rows{rows},
          m_screen{screen},
          m_path{path},
          m_cursor{cursor},
          m_commandline{commandline} {}
    ~TFMRenderer() = default;

    void buf_append(const std::string& data);
    void buf_clear();

    void adjust_scroll();
    void draw();
    void display();
    void path_insert();
};

#endif