#include "command_parser.hpp"

#include <sstream>

TFMCommand TFMCommandParser::parse(const std::string& cmd) const {
    std::istringstream iss(cmd);
    std::string buf;

    TFMCommand res;
    iss >> res.name;

    while (iss >> buf) {
        // divide flags if needed
        if (buf[0] == '-') {
            for (size_t i = 1; i < buf.length(); i++) {
                res.flags.push_back(std::string(1, buf[i]));
            }
        } else {
            res.positional.push_back(buf);
        }
    }

    return res;
}