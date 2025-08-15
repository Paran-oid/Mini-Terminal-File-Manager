#pragma once

#include <cstddef>
#include <cstdint>

struct TFMScreenDetails {
    size_t rows, cols;
    size_t row_off;
};

class TFMScreen {
   private:
    TFMScreenDetails m_app_screen;

    static void handle_exit(int32_t sig);
    static void window_size_update(int32_t sig);

   public:
    static TFMScreen* ms_instance;

    TFMScreen() : m_app_screen{0, 0, 0} {
        terminal_init();
        update_dimensions(0);
    }
    ~TFMScreen() { terminal_destroy(); };

    TFMScreenDetails get() const { return m_app_screen; }
    void set(const TFMScreenDetails& new_screen) { m_app_screen = new_screen; }

    size_t get_rows() const { return m_app_screen.rows; }
    void set_rows(size_t rows) { m_app_screen.rows = rows; }

    size_t get_cols() const { return m_app_screen.cols; }
    void set_cols(size_t cols) { m_app_screen.cols = cols; }

    size_t get_row_off() const { return m_app_screen.row_off; }
    void set_row_off(size_t row_off) { m_app_screen.row_off = row_off; }

    void update_dimensions(int32_t sig);
    void terminal_init();
    void terminal_destroy();
};
