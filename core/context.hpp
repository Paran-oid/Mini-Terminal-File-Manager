#ifndef CONTEXT_H
#define CONTEXT_H

#include <unistd.h>

#include <cstdint>
#include <filesystem>
#include <string>
#include <vector>

struct TFM_Cursor {
    int32_t cx = 0;
    int32_t cy = 0;
};

class TFM_Context {
   private:
    TFM_Cursor m_cursor;
    std::filesystem::path m_dir;

    std::vector<std::string> m_input_buf;

   public:
    TFM_Context() : m_cursor{0, 0}, m_dir(std::filesystem::current_path()){};
    ~TFM_Context() = default;

    // getters/setters
    const TFM_Cursor& cursor_get() const { return m_cursor; }
    void cursor_set(const TFM_Cursor& cursor) { m_cursor = cursor; }

    const std::filesystem::path& working_dir_get() const { return m_dir; }
    void working_dir_set(const std::filesystem::path& dir) { m_dir = dir; }

    const std::vector<std::string>& input_buf_get() const {
        return m_input_buf;
    }
    void input_buf_set(const std::vector<std::string>& input_buf) {
        m_input_buf = input_buf;
    }

    // methods
    void input_buf_clear() { m_input_buf.clear(); }
};

void ncurses_init();
void ncurses_destroy();

#endif