#ifndef COMMANDLINE_HPP
#define COMMANDLINE_HPP

#include <cstdint>
#include <string>

struct Commandline {
    std::string data;
    size_t row_index;
    size_t size;
};

class TFMCommandline {
   private:
    Commandline m_commandline;

   public:
    TFMCommandline() = default;
    ~TFMCommandline() = default;

    Commandline get() const { return m_commandline; }
    void set(const Commandline& commandline) { m_commandline = commandline; }

    std::string get_data() const { return m_commandline.data; }
    void set_data(const std::string& d) { m_commandline.data = d; }

    size_t get_row_index() const { return m_commandline.row_index; }
    void set_row_index(size_t ri) { m_commandline.row_index = ri; }

    size_t get_size() const { return m_commandline.size; }
    void set_size(size_t s) { m_commandline.size = s; }
};

#endif
