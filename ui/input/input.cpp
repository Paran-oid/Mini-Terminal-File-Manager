#include "input.hpp"

#include <ncurses.h>

#include "builtins.hpp"
#include "context.hpp"
#include "string_utils.hpp"

uint8_t TFM_handle_input_buf(TFM_Context& context,
                             std::vector<std::string>& output,
                             std::string& command) {
    for (const auto& b_command : builtin_commands) {
        if (command == b_command.first) {
            b_command.second(context, command);
            return EXIT_SUCCESS;
        }
    }

    std::string msg_error = command + ": command not found\n";
    printw("%s", msg_error.c_str());
    return EXIT_FAILURE;
}

uint8_t TFM_input_process(TFM_Context& context) {
    char input_buf[256];
    getstr(input_buf);
    std::string input(input_buf);

    input = trim(input);
    std::vector<std::string> output;
    TFM_handle_input_buf(context, output, input);

    context.input_buf_set(output);
    return EXIT_SUCCESS;
}