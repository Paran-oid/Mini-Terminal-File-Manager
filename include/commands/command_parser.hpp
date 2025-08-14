#pragma once

#include <string>
#include <vector>

struct TFMCommand {
    std::string name;
    std::vector<std::string> flags;
    std::vector<std::string> positional;
};

class TFMCommandParser {
   private:
   public:
    TFMCommandParser() = default;
    ~TFMCommandParser() = default;

    TFMCommand parse(const std::string& command) const;
};
