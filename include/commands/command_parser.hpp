#ifndef COMMAND_PARSER_HPP
#define COMMAND_PARSER_HPP

#include <string>
#include <vector>

struct TFMCommand {
    std::string name;
    std::vector<std::string> args;

    bool empty() { return name.empty(); }
};

class TFMCommandParser {
   private:
   public:
    TFMCommandParser() = default;
    ~TFMCommandParser() = default;

    TFMCommand parse(const std::string& command) const;
};

#endif