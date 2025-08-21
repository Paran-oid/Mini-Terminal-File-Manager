#pragma once

#include <cstdint>
#include <string>

struct TFMCommandLineDetails {
    std::string data;
    size_t last_row_index;
    size_t size;
};

class TFMCommandLine {
   private:
    TFMCommandLineDetails m_app_command_line;

   public:
    TFMCommandLine() = default;
    ~TFMCommandLine() = default;

    TFMCommandLineDetails get() const { return m_app_command_line; }
    void set(const TFMCommandLineDetails& command_line) {
        m_app_command_line = command_line;
    }

    std::string get_data() const { return m_app_command_line.data; }
    void set_data(const std::string& d) { m_app_command_line.data = d; }

    size_t get_last_row_index() const {
        return m_app_command_line.last_row_index;
    }
    void set_last_row_index(size_t ri) { m_app_command_line.last_row_index = ri; }

    size_t get_size() const { return m_app_command_line.size; }
    void set_size(size_t s) { m_app_command_line.size = s; }
};
