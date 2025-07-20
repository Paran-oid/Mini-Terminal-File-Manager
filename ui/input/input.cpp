#include "input.hpp"

#include <ncurses.h>

#include "builtins.hpp"

uint8_t TFM_handle_input_buf(std::vector<std::string>& output,
                             const std::string& buf) {
    for (const auto& command : builtin_commands) {
    }
    return EXIT_SUCCESS;
}

uint8_t TFM_input_process(TFM_Context& context) {
    char buf[256];
    getstr(buf);

    std::vector<std::string> output;
    TFM_handle_input_buf(output, buf);

    context.input_buf_set(output);
    return EXIT_SUCCESS;
}