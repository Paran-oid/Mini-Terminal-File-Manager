#include "rows.hpp"

#include <cmath>
#include <stdexcept>

#include "screen.hpp"

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

void TFMRows::remove(size_t index) {
    if (index >= m_app_rows.size()) {
        throw std::out_of_range("TFMRows: passed an invalid 'index' paramter");
    }

    m_app_rows.erase(m_app_rows.begin() + static_cast<diff_t>(index));
}

void TFMRows::remove_last() { m_app_rows.pop_back(); }

void TFMRows::remove_from(size_t index) {
    if (index >= m_app_rows.size()) {
        throw std::out_of_range("TFMRows: passed an invalid 'index' paramter");
    }

    m_app_rows.erase(m_app_rows.begin() + static_cast<diff_t>(index),
                     m_app_rows.end());
}

void TFMRows::refresh(size_t starting_index) {
    if (this->is_empty()) {
        return;
    }

    size_t cols = m_screen.get_cols();

    // handle underflow if any
    for (size_t i = starting_index; i < this->size() - 1; i++) {
        std::string& row = this->at(i);
        size_t len = row.length();

        if (len < cols && i + 1 < this->size()) {
            std::string& next_row = this->at(i + 1);
            size_t needed = cols - len;

            std::string to_add = next_row.substr(0, needed);
            row += to_add;
            next_row = next_row.substr(needed);

            if (next_row.empty()) {
                this->remove_last();
            }
        }
    }

    // handle overflow if any
    for (size_t i = starting_index; i < this->size(); i++) {
        std::string& row = this->at(i);
        size_t len = row.length();

        int32_t diff = static_cast<int32_t>(cols) - static_cast<int32_t>(len);

        // user appended text to a full string
        if (diff < 0) {
            diff = -diff;
            std::string extra = row.substr(cols, static_cast<size_t>(diff));
            row = row.substr(0, cols);
            if (this->size() < i + 1) {
                this->append("");
            }
            std::string& last_row = this->back();
            last_row = extra + last_row;
        }
    }
}

void TFMRows::clear() { m_app_rows.clear(); }

bool TFMRows::is_empty() { return this->size() == 0; }