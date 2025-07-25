#ifndef PARSER_HPP
#define PARSE_HPP

#include <string>
#include <vector>

struct Command {
    std::string name;
    std::vector<std::string> args;
};

Command parser_command(const std::string& input);

#endif
