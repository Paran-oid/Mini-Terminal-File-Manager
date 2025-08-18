#pragma once
#include <string>

class TFMRenderer;
class TFMRows;

class TFMDialog {
   private:
    TFMRenderer& m_renderer;
    TFMRows& m_rows;

   public:
    TFMDialog(TFMRenderer& renderer, TFMRows& rows)
        : m_renderer{renderer}, m_rows{rows} {}

    std::string receive(const std::string& message);
}