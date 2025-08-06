#include "command_handler.hpp"

void TFMCommandHandler::process(const std::string& command) {
    std::vector<std::string> args = this->parse(command);

    if (args.empty()) {
        // *display that no command was found
    }

    switch (args[0]) {
        case "cd":
            navigate(args);
            break;
        case "ls":
            list(args);
            break;
        default:
            // *display that no command was found
            break;
    }
}