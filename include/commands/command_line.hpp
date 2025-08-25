#pragma once

#include <cstdint>
#include <string>

/**
 * @brief Describes a command line's content
 *
 */
struct TFMCommandLineDetails {
    std::string data;       ///< content of this precise command
    size_t last_row_index;  ///< last row index
    size_t size;            ///< allocated size
};

/**
 * @brief Handles command line related functionalities
 *
 */
class TFMCommandLine {
   private:
    TFMCommandLineDetails m_app_command_line;

   public:
    /**
     * @brief Construct a new TFMCommandLine object
     *
     */
    TFMCommandLine() = default;

    /**
     * @brief Destroy the TFMCommandLine object
     *
     */
    ~TFMCommandLine() = default;

    /**
     * @brief Gets the current command line
     *
     * @return TFMCommandLineDetails
     */
    TFMCommandLineDetails get() const { return m_app_command_line; }

    /**
     * @brief Sets the current command line
     *
     * @param command_line
     */
    void set(const TFMCommandLineDetails& command_line) {
        m_app_command_line = command_line;
    }

    /**
     * @brief Get the data object
     *
     * @return std::string
     */
    std::string get_data() const { return m_app_command_line.data; }

    /**
     * @brief Set the data object
     *
     * @param d
     */
    void set_data(const std::string& d) { m_app_command_line.data = d; }

    /**
     * @brief Get the last row index object
     *
     * @return size_t
     */
    size_t get_last_row_index() const {
        return m_app_command_line.last_row_index;
    }

    /**
     * @brief Set the last row index object
     *
     * @param ri
     */
    void set_last_row_index(size_t ri) {
        m_app_command_line.last_row_index = ri;
    }

    /**
     * @brief Get the size object
     *
     * @return size_t
     */
    size_t get_size() const { return m_app_command_line.size; }

    /**
     * @brief Set the size object
     *
     * @param s
     */
    void set_size(size_t s) { m_app_command_line.size = s; }
};
