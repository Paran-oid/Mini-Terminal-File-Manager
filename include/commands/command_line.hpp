#ifndef command_line_HPP
#define command_line_HPP

#include <cstdint>
#include <string>

struct command_line {
    std::string data;
    size_t row_index;
    size_t size;
};

class TFMCommandLine {
   private:
    command_line m_command_line;

   public:
    TFMCommandLine() = default;
    ~TFMCommandLine() = default;

    command_line get() const { return m_command_line; }
    void set(const command_line& command_line) {
        m_command_line = command_line;
    }

    std::string get_data() const { return m_command_line.data; }
    void set_data(const std::string& d) { m_command_line.data = d; }

    size_t get_row_index() const { return m_command_line.row_index; }
    void set_row_index(size_t ri) { m_command_line.row_index = ri; }

    size_t get_size() const { return m_command_line.size; }
    void set_size(size_t s) { m_command_line.size = s; }
};

#endif
