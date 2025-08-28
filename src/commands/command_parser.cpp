#include "command_parser.hpp"

#include <sstream>

TFM::Command TFM::CommandParser::parse(const std::string& cmd) const {
    std::istringstream iss(cmd);
    std::string buf;

    TFM::Command res;
    iss >> res.name;
    size_t idx = 0;

    while (iss >> buf) {
        if (buf.substr(0, 2) == "--") {
            res.long_flags.push_back({buf.substr(2), idx++});
        } else if (buf[0] == '-') {
            for (size_t i = 1; i < buf.length(); i++) {
                res.short_flags.push_back({std::string{buf[i]}, idx++});
            }
        } else {
            res.positional.push_back({buf, idx++});
        }
    }

    return res;
}