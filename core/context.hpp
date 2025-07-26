#ifndef CONTEXT_H
#define CONTEXT_H

#include <sys/ioctl.h>
#include <unistd.h>

#include <cstdint>
#include <filesystem>
#include <string>
#include <vector>

struct TFM_Command {
    std::string name;
    std::vector<std::string> args;
};

class TFM_Context {
   private:
    // first: rows, second: cols
    std::pair<int32_t, int32_t> m_screen_dimensions;
    // first: cx, second: cy
    std::pair<int32_t, int32_t> m_cursor;
    std::filesystem::path m_cur_dir;
    std::vector<std::string> m_input_buf;

   public:
    TFM_Context() : m_cur_dir(std::filesystem::current_path()) {
        struct winsize win;
        ioctl(STDOUT_FILENO, TIOCGWINSZ, &win);
        m_screen_dimensions.first = win.ws_row;
        m_screen_dimensions.second = win.ws_col;
    }
    ~TFM_Context() = default;

    // getters/setters
    const std::filesystem::path& working_dir_get() const { return m_cur_dir; }
    void working_dir_set(const std::filesystem::path& dir) { m_cur_dir = dir; }

    const std::vector<std::string>& input_buf_get() const {
        return m_input_buf;
    }
    void input_buf_set(const std::vector<std::string>& input_buf) {
        m_input_buf = input_buf;
    }

    const std::pair<int32_t, int32_t>& screen_dimensions_get() const {
        return m_screen_dimensions;
    }
    void screen_dimensions_set(
        const std::pair<int32_t, int32_t>& screen_dimensions) {
        m_screen_dimensions = screen_dimensions;
    }

    // methods
    void input_buf_clear() { m_input_buf.clear(); }
};

void ncurses_init();
void ncurses_destroy();
void signals_remap();

#endif