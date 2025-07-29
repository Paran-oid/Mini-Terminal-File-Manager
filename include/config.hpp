#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <filesystem>
#include <string>
#include <vector>

#define die(msg) (_die(__FILE__, __LINE__, msg))

void _die(const std::string& filename, int32_t line,
          const std::string& message);

struct Cursor {
    int32_t cx, cy;
};

struct Screen {
    int32_t rows, cols;
    int32_t row_off, col_off;
};

// Stores app-wide state
class TFMConfig {
   private:
    // holds visible file entries
    std::vector<std::string> m_rows;
    Cursor m_cursor;
    Screen m_screen;

    std::filesystem::path m_current_path;
    uint8_t m_started = 0;

   public:
    TFMConfig()
        : m_current_path{std::filesystem::current_path()}, m_cursor{0, 0} {}
    ~TFMConfig() {}

    // Getter and Setter for m_started
    const uint8_t get_started() const { return m_started; }
    uint8_t get_started() { return m_started; }
    void set_started(const uint8_t started) { m_started = started; }

    // Getter and Setter for m_current_path
    const std::filesystem::path& get_current_path() const {
        return m_current_path;
    }
    std::filesystem::path& get_current_path() { return m_current_path; }
    void set_current_path(const std::filesystem::path& new_current_path) {
        m_current_path = new_current_path;
    }

    // Getter and Setter for m_rows
    const std::vector<std::string>& get_rows() const { return m_rows; }
    std::vector<std::string>& get_rows() { return m_rows; }
    void set_rows(const std::vector<std::string>& new_rows) {
        m_rows = new_rows;
    }

    // Getter and Setter for m_cursor
    Cursor get_cursor() const { return m_cursor; }
    void set_cursor(const Cursor& new_cursor) { m_cursor = new_cursor; }

    // Convenience getters and setters for m_cursor components
    int32_t get_cursor_cx() const { return m_cursor.cx; }
    int32_t get_cursor_cy() const { return m_cursor.cy; }
    void set_cursor_cx(int32_t cx) { m_cursor.cx = cx; }
    void set_cursor_cy(int32_t cy) { m_cursor.cy = cy; }

    // Getter and Setter for m_screen
    Screen get_screen() const { return m_screen; }
    void set_screen(const Screen& new_screen) { m_screen = new_screen; }

    // Convenience getters and setters for m_screen fields
    int32_t get_screen_rows() const { return m_screen.rows; }
    int32_t get_screen_cols() const { return m_screen.cols; }
    int32_t get_screen_row_off() const { return m_screen.row_off; }
    int32_t get_screen_col_off() const { return m_screen.col_off; }
    void set_screen_rows(int32_t rows) { m_screen.rows = rows; }
    void set_screen_cols(int32_t cols) { m_screen.cols = cols; }
    void set_screen_row_off(int32_t row_off) { m_screen.row_off = row_off; }
    void set_screen_col_off(int32_t col_off) { m_screen.col_off = col_off; }

    void screen_dimensions_update();
    void append_row(const std::string&);
};

#endif