#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <iostream>
#include <string>
#include <vector>

class TFMConfig {
   private:
    std::string username;
    bool m_command_state = 0;
    bool m_program_state = 1;
    bool show_hidden_files = 0;

   public:
    TFMConfig() { username = std::getenv("USER"); };
    ~TFMConfig() = default;

    const std::string& get_username() const { return username; }
    void set_username(const std::string& user) { username = user; }

    bool is_in_command() { return m_command_state; }
    void enable_command() { m_command_state = 1; }
    void disable_command() { m_command_state = 0; }

    bool is_program_running() { return m_program_state; }
    void start_program() { m_program_state = 1; }
    void end_program() { m_program_state = 0; }
};

#endif