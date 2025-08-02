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

    void pop_back();
    void append(const std::string& data);
    void update(const std::string& data, size_t at);
    void format_string_to_rows(const std::string& data);  // TODO
};

#endif