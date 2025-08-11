#include "rows.hpp"

#include <cmath>
#include <stdexcept>

#include "screen.hpp"

void TFMRows::append(const std::string& data) {
    if (data.empty()) {
        m_app_rows.push_back("");
        return;
    }

    size_t cols = static_cast<size_t>(m_screen.get_cols());
    size_t rows = static_cast<size_t>(std::ceil(
        (static_cast<float>(data.size()) / static_cast<float>(cols))));

    size_t from = 0;
    for (size_t i = 0; i < rows; i++) {
        m_app_rows.push_back(data.substr(from, cols));
        from += cols;
    }
}

void TFMRows::update(const std::string& data, size_t at) {
    if (at >= m_app_rows.size()) {
        throw std::out_of_range("TFMRows: passed an invalid 'at' paramter");
    }

    m_app_rows[at] = data;
}

void TFMRows::remove_from(size_t at) {
    if (at >= m_app_rows.size()) {
        throw std::out_of_range("TFMRows: passed an invalid 'at' paramter");
    }

    m_app_rows.erase(m_app_rows.begin() + static_cast<diff_t>(at),
                     m_app_rows.end());
}
void TFMRows::remove(size_t at) {
    if (at >= m_app_rows.size()) {
        throw std::out_of_range("TFMRows: passed an invalid 'at' paramter");
    }

    m_app_rows.erase(m_app_rows.begin() + static_cast<diff_t>(at));
}

void TFMRows::pop_back() { m_app_rows.pop_back(); }

std::string TFMRows::at(size_t at) const {
    if (at >= m_app_rows.size()) {
        throw std::out_of_range("TFMRows: passed an invalid 'at' paramter");
    }
    return m_app_rows[at];
}

std::string TFMRows::front() { return m_app_rows.front(); }
std::string TFMRows::back() { return m_app_rows.back(); }

size_t TFMRows::size() const { return m_app_rows.size(); }

void TFMRows::clear() { m_app_rows.clear(); }
