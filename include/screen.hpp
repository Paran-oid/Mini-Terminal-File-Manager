#ifndef SCREEN_HPP
#define SCREEN_HPP

#include <cstdint>

struct TFMScreenDetails {
    int32_t rows, cols;
    int32_t row_off;
};

class TFMScreen {
   private:
    TFMScreenDetails m_screen;

    static void handle_exit(int32_t sig);
    static void window_size_update(int32_t sig);

   public:
    static TFMScreen* ms_instance;

    TFMScreen() : m_screen{0, 0, 0} {
        terminal_init();
        update_dimensions(0);
    }
    ~TFMScreen() { terminal_destroy(); };

    TFMScreenDetails get() const { return m_screen; }
    void set(const TFMScreenDetails& new_screen) { m_screen = new_screen; }

    int32_t get_rows() const { return m_screen.rows; }
    void set_rows(int32_t rows) { m_screen.rows = rows; }

    int32_t get_cols() const { return m_screen.cols; }
    void set_cols(int32_t cols) { m_screen.cols = cols; }

    int32_t get_row_off() const { return m_screen.row_off; }
    void set_row_off(int32_t row_off) { m_screen.row_off = row_off; }

    void update_dimensions(int32_t sig);
    void terminal_destroy();
    void terminal_init();
};

#endif
