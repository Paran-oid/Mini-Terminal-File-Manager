#include "input.hpp"

#include <ncurses.h>

#include "builtins.hpp"
#include "context.hpp"
#include "parser.hpp"
#include "string_utils.hpp"

uint8_t TFM_handle_input_buf(TFM_Context& context,
                             std::vector<std::string>& output,
                             std::string& buf_inp) {
    TFM_Command cmd = parser_command(buf_inp);

    if (cmd.name.empty()) return EXIT_FAILURE;

    for (const auto& cur_cmd : builtin_TFM_Commands) {
        if (cmd.name == cur_cmd.first) {
            cur_cmd.second(context, cmd);
            return EXIT_SUCCESS;
        }
    }

    std::string msg_error = buf_inp + ": TFM_Command not found\n";
    printw("%s", msg_error.c_str());
    return EXIT_FAILURE;
}

uint8_t TFM_input_process(TFM_Context& context) {
    char input_buf[256];
    getstr(input_buf);
    std::string input(trim(input_buf));

    // TODO: need to make arrows not delete chars?

    std::vector<std::string> output;
    TFM_handle_input_buf(context, output, input);

    context.input_buf_set(output);
    return EXIT_SUCCESS;
}