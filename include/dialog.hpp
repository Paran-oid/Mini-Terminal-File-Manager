#pragma once
#include <string>

class TFMRenderer;
class TFMConfig;
class TFMInput;

class TFMDialog {
   private:
    TFMRenderer& m_renderer;
    TFMConfig& m_config;
    TFMInput& m_input;

   public:
    TFMDialog(TFMRenderer& renderer, TFMConfig& config, TFMInput& input)
        : m_renderer{renderer}, m_config{config}, m_input{input} {}
    ~TFMDialog() = default;

    std::string receive(const std::string& message);
};