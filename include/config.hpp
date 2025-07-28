#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <ncurses.h>

#include <cstdio>
#include <string>
#include <vector>

#define die(msg) (_die(__FILE__, __LINE__, msg))

void _die(const std::string& filename, int32_t line,
          const std::string& message);

// rows

struct Row {
    std::string data;
    size_t size;
};

class TFMContentBuffer {
   private:
    std::vector<Row> rows;

   public:
    void append_row(const std::string& text) {
        rows.push_back({text, text.size()});
    }

    const std::vector<Row>& get_rows() const { return rows; }

    size_t num_rows() const { return rows.size(); }
};

// config

struct Cursor {
    int32_t cx, cy;
};

struct Screen {
    int32_t rows, cols;
    int32_t row_off, col_off;
};

class TFMConfig {
   private:
    std::pair<int32_t, int32_t> cursor;
    Screen screen;

   public:
    TFMContentBuffer data;

    void screen_dimensions_update() {
        getmaxyx(stdscr, screen.rows, screen.cols);
    }
};

#endif