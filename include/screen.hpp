#pragma once

#include <cstddef>
#include <cstdint>

namespace TFM {

/**
 * @brief Describes the details of the current screen
 *
 */
struct ScreenDetails {
    size_t rows;     ///< max rows of screen
    size_t cols;     ///< max cols of screen
    size_t row_off;  ///< row offset of current screen
};

/**
 * @brief Responsible for screen configuration (cols,rows,rowoff) and ncurses
 * settings
 *
 */
class Screen {
   private:
    ScreenDetails m_app_screen;

    /**
     * @brief Handles app's exit
     *
     * @param sig
     */
    static void handle_exit(int32_t sig);

    /**
     * @brief Updates window's dimensions if window's size changed
     * @todo MUST IMPLEMENT
     *
     * @param sig
     */
    static void window_size_update(int32_t sig);

   public:
    /**
     * @brief static public member used primarly to assign it to current
     * Screen class and to be able to handle updating window dimensions
     * directly
     *
     */
    static Screen* ms_instance;

    /**
     * @brief Construct a new Screen object
     *
     */
    Screen() : m_app_screen{0, 0, 0} {
        terminal_init();
        update_dimensions(0);
    }

    /**
     * @brief Destroy the Screen object
     *
     */
    ~Screen() { terminal_destroy(); };

    /**
     * @brief Get screen details
     *
     * @return ScreenDetails
     */
    ScreenDetails get() const { return m_app_screen; }

    /**
     * @brief Set screen details
     *
     * @param new_screen
     */
    void set(const ScreenDetails& new_screen) { m_app_screen = new_screen; }

    /**
     * @brief Get the max rows
     *
     * @return size_t
     */
    size_t get_rows() const { return m_app_screen.rows; }
    /**
     * @brief Set the max rows
     *
     * @param rows
     */
    void set_rows(size_t rows) { m_app_screen.rows = rows; }

    /**
     * @brief Get the max cols
     *
     * @return size_t
     */
    size_t get_cols() const { return m_app_screen.cols; }

    /**
     * @brief Set the max cols
     *
     * @param cols
     */
    void set_cols(size_t cols) { m_app_screen.cols = cols; }

    /**
     * @brief Get the row off object
     *
     * @return size_t
     */
    size_t get_row_off() const { return m_app_screen.row_off; }

    /**
     * @brief Set the row off object
     *
     * @param row_off
     */
    void set_row_off(size_t row_off) { m_app_screen.row_off = row_off; }

    /**
     * @brief Updates dimensions
     *
     * @param sig (redundant but just so that this function can be passed to
     * updating window's dimensions)
     */
    void update_dimensions(int32_t sig);

    /**
     * @brief Initializes terminal (ncurses)
     *
     */
    void terminal_init();

    /**
     * @brief Destroys terminal (ncurses)
     *
     */
    void terminal_destroy();
};

}  // namespace TFM
