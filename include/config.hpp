#pragma once

#include <iostream>
#include <string>
#include <vector>

class TFMConfig {
   private:
    std::string m_username;
    bool m_command_state;
    bool m_program_state;

   public:
    TFMConfig() : m_command_state{false}, m_program_state{true} {
        m_username = std::getenv("USER");
    };
    ~TFMConfig() = default;

    const std::string& get_username() const { return m_username; }
    void set_username(const std::string& username) { m_username = username; }

    bool is_in_command() { return m_command_state; }
    void enable_command() { m_command_state = 1; }
    void disable_command() { m_command_state = 0; }

    bool is_program_running() { return m_program_state; }
    void start_program() { m_program_state = 1; }
    void end_program() { m_program_state = 0; }
};
