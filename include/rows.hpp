#ifndef ROWS_HPP
#define ROWS_HPP

#include <cstdint>
#include <string>
#include <vector>

class TFMRows {
   private:
    std::vector<std::string> m_rows;

   public:
    TFMRows() = default;
    ~TFMRows() = default;

    std::string at(size_t at) const;
    std::string front();
    std::string back();
    size_t size() const;

    void update(const std::string& data, size_t at);
    void append(const std::string& data);
    void pop_back();
    void clear();
};

#endif