#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <filesystem>
#include <string>
#include <vector>

class TFMConfig {
   private:
    bool m_command_state = 0;
    bool m_program_state = 1;

   public:
    TFMConfig() = default;
    ~TFMConfig() = default;

    bool is_in_command() { return m_command_state; }
    void enable_command() { m_command_state = 1; }
    void disable_command() { m_command_state = 0; }

    bool is_program_running() { return m_program_state; }
    void start_program() { m_program_state = 1; }
    void end_program() { m_program_state = 0; }
};

#endif