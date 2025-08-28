#pragma once
#include <string>

namespace TFM {

class Renderer;
class Config;
class Input;

/**
 * @brief Responsible for retrieving user input if prompted
 *
 */
class Dialog {
   private:
    Renderer& m_renderer;
    Config& m_config;
    Input& m_input;

   public:
    /**
     * @brief Construct a new Dialog object
     *
     * @param renderer
     * @param config
     * @param input
     */
    Dialog(Renderer& renderer, Config& config, Input& input)
        : m_renderer{renderer}, m_config{config}, m_input{input} {}

    /**
     * @brief Destroy the Dialog object
     *
     */
    ~Dialog() = default;

    /**
     * @brief prompts user for input along with entering a message
     *
     * @param message
     * @return std::string
     */
    std::string prompt(const std::string& message);
};

}  // namespace TFM
