#ifndef ROWS_HPP
#define ROWS_HPP

#include <cstdint>
#include <string>
#include <vector>

using diff_t = std::vector<std::string>::difference_type;

class TFMScreen;

class TFMRows {
   private:
    // TODO: remove all references of other classes???
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

    // TODO: remove all of these under me
    void update(const std::string& data,
                size_t index);  // TODO: remove this and let user directly add
                                // TODO: when he makes a reference
    void append(const std::string& data);  // TODO: remove
    void remove_from(size_t index);
    void remove(size_t index);
    void pop_back();
    void clear();

    bool empty();
};

#endif