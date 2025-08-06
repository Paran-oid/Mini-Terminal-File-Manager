#ifndef COMMAND_HANDLER_HPP
#define COMMAND_HANDLER_HPP

#include <string>
#include <vector>

class TFMCommandHandler {
   private:
    // TODO: make some kind of map that maps from string to functions (so we
    // TODO: don't have to use a switch statement)

    std::vector<std::string> parse(const std::string& command);
    void navigate(const std::vector<std::string>& command);
    void list(const std::vector<std::string>& command);

   public:
    TFMCommandHandler() = default;
    ~TFMCommandHandler() = default;

    void process(const std::string& command);
};

#endif