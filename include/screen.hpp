#ifndef SCREEN_HPP
#define SCREEN_HPP

#include <cstdint>

struct Screen {
    int32_t rows, cols;
    int32_t row_off, col_off;
};

class TFMScreen {
   private:
    Screen m_screen;

   public:
    TFMScreen() { update_dimensions(); }
    ~TFMScreen() = default;

    Screen get() const { return m_screen; }
    void set(const Screen& new_screen) { m_screen = new_screen; }

    int32_t get_rows() const { return m_screen.rows; }
    void set_rows(int32_t r) { m_screen.rows = r; }

    int32_t get_cols() const { return m_screen.cols; }
    void set_cols(int32_t c) { m_screen.cols = c; }

    int32_t get_row_off() const { return m_screen.row_off; }
    void set_row_off(int32_t ro) { m_screen.row_off = ro; }

    int32_t get_col_off() const { return m_screen.col_off; }
    void set_col_off(int32_t co) { m_screen.col_off = co; }

    void update_dimensions();
};

#endif
