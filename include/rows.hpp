#ifndef ROWS_HPP
#define ROWS_HPP

#include <cstdint>
#include <string>
#include <vector>

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

    void pop_back();
    void update(const std::string& data, size_t at);
    void append(const std::string& data);
    void clear();
};

#endif