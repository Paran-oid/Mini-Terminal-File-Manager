#pragma once

#include <cstdint>
#include <string>
#include <vector>

using diff_t = std::vector<std::string>::difference_type;

class TFMScreen;

/**
 * @brief Manages everything related to rows
 *
 */
class TFMRows {
   private:
    TFMScreen& m_screen;

    std::vector<std::string> m_app_rows;

   public:
    /**
     * @brief Construct a new TFMRows object
     *
     * @param screen
     */
    TFMRows(TFMScreen& screen) : m_screen{screen} {};
    ~TFMRows() = default;

    /**
     * @brief Gets row at index (reference)
     *
     * @param index
     * @return std::string&
     */
    std::string& at(size_t index);

    /**
     * @brief Gets row at index (copy/const reference)
     *
     * @param index
     * @return const std::string&
     */
    const std::string& at(size_t index) const;

    /**
     * @brief Gets row at front of the rows buf (reference)
     *
     * @return std::string&
     */
    std::string& front();

    /**
     * @brief Gets row at front of the rows buf (copy/const reference)
     *
     * @return const std::string&
     */
    const std::string& front() const;

    /**
     * @brief Gets row at back of the rows buf (reference)
     *
     * @return std::string&
     */
    std::string& back();

    /**
     * @brief Gets row at back of the rows buf (copy/const reference)
     *
     * @return const std::string&
     */
    const std::string& back() const;

    /**
     * @brief Returns the size of rows_buf
     *
     * @return size_t
     */
    size_t size() const;

    /**
     * @brief Adds a new row to rows_buf and makes sure it doesn't
     * exceeds the cols limit
     *
     * @param row
     */
    void append(const std::string& row);

    /**
     * @brief Removes a row at index
     *
     * @param index
     */
    void remove(size_t index);

    /**
     * @brief Remove last row
     *
     */
    void remove_last();

    /**
     * @brief Removes all rows starting from an index
     *
     * @param index
     */
    void remove_from(size_t index);

    /**
     * @brief Refreshes all rows by ensuring that each row is correctly
     * formatted
     *
     * @param starting_index
     */
    void refresh(size_t starting_index);

    /**
     * @brief Gets rid of all present rows
     *
     */
    void clear();

    /**
     * @brief Returns if there are no rows
     *
     * @return true
     * @return false
     */
    bool is_empty();
};
