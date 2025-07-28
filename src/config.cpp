#include "config.hpp"

void _die(const std::string& filename, int32_t line,
          const std::string& message) {
    endwin();
    fprintf(stderr, "Error at %s:%d: %s\n", filename.c_str(), line,
            message.c_str());
    std::exit(1);
}