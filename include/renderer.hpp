#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <cstdint>
#include <sstream>

// responsible for drawing
class TFMConfig;

class TFMRenderer {
   private:
    std::ostringstream m_abuf;
    TFMConfig& m_conf;

   public:
    TFMRenderer(TFMConfig& conf) : m_conf{conf} {}

    void buf_append(const std::string&);

    uint8_t adjust_scroll();
    uint8_t draw();
    uint8_t display();
};

#endif