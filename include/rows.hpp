#pragma once

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

    std::string& at(size_t index);
    const std::string& at(size_t index) const;

    std::string& front();
    const std::string& front() const;

    std::string& back();
    const std::string& back() const;

    size_t size() const;

    void append(const std::string& row);
    void remove(size_t index);
    void remove_last();
    void remove_from(size_t index);

    void refresh(size_t starting_index);
    void clear();

    bool is_empty();
};
