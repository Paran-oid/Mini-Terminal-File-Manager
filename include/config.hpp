#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <filesystem>
#include <string>
#include <vector>

struct Cursor {
    int32_t cx, cy;
};

struct Screen {
    int32_t rows, cols;
    int32_t row_off, col_off;
};

struct Commandline {
    std::string data;
    size_t row_index;
    size_t size;
};

// TODO: make sure each class has only one single purpose

// Stores app-wide state
class TFMConfig {
   private:
    // holds visible file entries
    std::vector<std::string> m_rows;
    Cursor m_cursor;
    Screen m_screen;
    Commandline m_commandline;

    std::filesystem::path m_current_path;
    uint8_t m_started = 0;

   public:
    // Constructor/Deconstructor

    TFMConfig()
        : m_current_path{std::filesystem::current_path()}, m_cursor{0, 0} {
        screen_dimensions_update();
    }
    ~TFMConfig() {}

    // Getters/Setters

    uint8_t get_started() const { return m_started; }
    void set_started(uint8_t started) { m_started = started; }

    std::filesystem::path get_current_path() const { return m_current_path; }
    void set_current_path(const std::filesystem::path new_current_path) {
        m_current_path = new_current_path;
    }

    Cursor get_cursor() { return m_cursor; }
    void set_cursor(const Cursor& new_cursor) { m_cursor = new_cursor; }

    Screen get_screen() const { return m_screen; }
    void set_screen(const Screen& new_screen) { m_screen = new_screen; }

    Commandline get_commandline() const { return m_commandline; }
    void set_commandline(const Commandline& new_commandline) {
        m_commandline = new_commandline;
    }

    // Methods
    void screen_dimensions_update();

    size_t rows_size() const;

    std::string row_at(int32_t at) const;
    uint8_t row_append(const std::string& data);
    uint8_t row_update(const std::string& data, int32_t at);

    // Checking

    uint8_t is_cursor_at_last_row();
    uint8_t is_cursor_at_commandline();
};

#endif