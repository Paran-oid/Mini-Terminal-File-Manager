#ifndef ROWS_HPP
#define ROWS_HPP

#include <cstdint>
#include <string>
#include <vector>

using diff_t = std::vector<std::string>::difference_type;

class TFMScreen;

class TFMRows {
   private:
    TFMScreen& m_screen;

    std::vector<std::string> m_app_rows;

   public:
    TFMRows(TFMScreen& screen) : m_screen{screen} {};
    ~TFMRows() = default;

    std::string at(size_t at) const;
    std::string front();
    std::string back();
    size_t size() const;

    void remove_from(size_t at);
    void pop_back();
    void remove(size_t at);
    void update(const std::string& data, size_t at);
    void append(const std::string& data);
    void clear();
};

#endif