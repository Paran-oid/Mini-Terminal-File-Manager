#include "rows.hpp"

#include <stdexcept>

void TFMRows::append(const std::string& data) {
    if (data.empty()) {
        std::invalid_argument("TFMRows: empty data passed in parameters");
    }

    m_rows.push_back(data);
}

void TFMRows::update(const std::string& data, size_t at) {
    if (at >= m_rows.size()) {
        throw std::out_of_range("TFMRows: passed an invalid 'at' paramter");
    }

    m_rows[at] = data;
}
void TFMRows::pop_back() { m_rows.pop_back(); }

std::string TFMRows::at(size_t at) const {
    if (at >= m_rows.size()) {
        throw std::out_of_range("TFMRows: passed an invalid 'at' paramter");
    }
    return m_rows[at];
}

std::string TFMRows::front() { return m_rows.front(); }
std::string TFMRows::back() { return m_rows.back(); }

size_t TFMRows::size() const { return m_rows.size(); }
