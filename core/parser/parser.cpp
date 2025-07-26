#include "parser.hpp"

#include <cstdint>
#include <sstream>

#include "builtins.hpp"
#include "context.hpp"

TFM_Command parser_command(const std::string& input) {
    TFM_Command c;
    std::istringstream iss(input);
    std::string token;
    uint8_t assigned_TFM_Command = 0;

    // TODO: handle edge cases where there is a space in an arg
    while (iss >> token) {
        if (!assigned_TFM_Command) {
            if (builtin_TFM_Commands.contains(token)) {
                assigned_TFM_Command = 1;
                c.name = token;
            }
        } else {
            c.args.push_back(token);
        }
    }
    return c;
}