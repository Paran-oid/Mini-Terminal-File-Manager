#include "command_parser.hpp"

#include <sstream>

TFMCommand TFMCommandParser::parse(const std::string& command) const {
    std::istringstream iss(command);
    std::string buf;

    TFMCommand res;
    iss >> res.name;

    while (iss >> buf) {
        res.args.push_back(buf);
    }

    return res;
}