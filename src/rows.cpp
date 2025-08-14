#include "rows.hpp"

#include <cmath>
#include <stdexcept>

#include "screen.hpp"

void TFMRows::append(const std::string& data) {
    if (data.empty()) {
        m_app_rows.push_back("");
        return;
    }

    size_t cols = m_screen.get_cols();
    size_t rows = static_cast<size_t>(std::ceil(
        (static_cast<float>(data.size()) / static_cast<float>(cols))));

    size_t from = 0;
    for (size_t i = 0; i < rows; i++) {
        m_app_rows.push_back(data.substr(from, cols));
        from += cols;
    }
}

void TFMRows::remove_from(size_t index) {
    if (index >= m_app_rows.size()) {
        throw std::out_of_range("TFMRows: passed an invalid 'index' paramter");
    }

    m_app_rows.erase(m_app_rows.begin() + static_cast<diff_t>(index),
                     m_app_rows.end());
}

void TFMRows::remove(size_t index) {
    if (index >= m_app_rows.size()) {
        throw std::out_of_range("TFMRows: passed an invalid 'index' paramter");
    }

    m_app_rows.erase(m_app_rows.begin() + static_cast<diff_t>(index));
}

void TFMRows::remove_last() { m_app_rows.pop_back(); }

std::string& TFMRows::at(size_t index) {
    if (index >= m_app_rows.size()) {
        throw std::out_of_range("TFMRows: passed an invalid 'index' paramter");
    }

    return m_app_rows[index];
}

const std::string& TFMRows::at(size_t index) const {
    if (index >= m_app_rows.size()) {
        throw std::out_of_range("TFMRows: passed an invalid 'index' paramter");
    }
    return m_app_rows[index];
}

std::string& TFMRows::front() { return m_app_rows.front(); }
const std::string& TFMRows::front() const { return m_app_rows.front(); }

std::string& TFMRows::back() { return m_app_rows.back(); }
const std::string& TFMRows::back() const { return m_app_rows.back(); }

size_t TFMRows::size() const { return m_app_rows.size(); }

void TFMRows::clear() { m_app_rows.clear(); }
bool TFMRows::is_empty() { return this->size() == 0; }
