#pragma once
#include <string>

class TFMRenderer;
class TFMConfig;
class TFMInput;

/**
 * @brief Responsible for retrieving user input if prompted
 *
 */
class TFMDialog {
   private:
    TFMRenderer& m_renderer;
    TFMConfig& m_config;
    TFMInput& m_input;

   public:
    /**
     * @brief Construct a new TFMDialog object
     *
     * @param renderer
     * @param config
     * @param input
     */
    TFMDialog(TFMRenderer& renderer, TFMConfig& config, TFMInput& input)
        : m_renderer{renderer}, m_config{config}, m_input{input} {}
    ~TFMDialog() = default;

    /**
     * @brief prompts user for input along with entering a message
     *
     * @param message
     * @return std::string
     */
    std::string prompt(const std::string& message);
};