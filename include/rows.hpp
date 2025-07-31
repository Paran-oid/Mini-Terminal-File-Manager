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

    size_t size() const;

    std::string at(int32_t at) const;
    uint8_t append(const std::string& data);
    uint8_t update(const std::string& data, int32_t at);
};

#endif