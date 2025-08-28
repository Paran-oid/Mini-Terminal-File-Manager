#pragma once

#include <iostream>
#include <string>
#include <vector>

namespace TFM {

/**
 * @brief configures defined program states and holds current username
 * of the user
 *
 */
class Config {
   private:
    std::string m_username;
    bool m_command_state;
    bool m_program_state;

   public:
    /**
     * @brief Construct a new Config object
     *
     */
    Config() { m_username = std::getenv("USER"); };

    /**
     * @brief Destroy the Config object
     *
     */
    ~Config() = default;

    /**
     * @brief Get the username object
     *
     * @return const std::string&
     */
    const std::string& get_username() const { return m_username; }

    /**
     * @brief Set the username object
     *
     * @param username
     */
    void set_username(const std::string& username) { m_username = username; }

    /**
     * @brief Checks if user is currently in a command
     *
     * @return true
     * @return false
     */
    bool is_in_command() { return m_command_state; }

    /**
     * @brief Enables command
     *
     */
    void enable_command() { m_command_state = 1; }

    /**
     * @brief Disables command
     *
     */
    void disable_command() { m_command_state = 0; }

    /**
     * @brief Checks if program is currently running
     *
     * @return true
     * @return false
     */
    bool is_program_running() { return m_program_state; }

    /**
     * @brief Start running program
     *
     */
    void start_program() { m_program_state = 1; }

    /**
     * @brief Ends programs
     *
     */
    void end_program() { m_program_state = 0; }
};

}  // namespace TFM
