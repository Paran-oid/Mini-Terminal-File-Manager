#include "rows.hpp"

uint8_t TFMRows::append(const std::string& data) {
    m_rows.push_back(data);
    return 0;
}

uint8_t TFMRows::update(const std::string& data, int32_t at) {
    if (at < 0 || at >= m_rows.size()) {
        return 1;
    }

    m_rows[at] = data;
    return 0;
}

std::string TFMRows::at(int32_t at) const { return m_rows[at]; }
size_t TFMRows::size() const { return m_rows.size(); }