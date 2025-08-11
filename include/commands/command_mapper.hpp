#ifndef COMMAND_MAPPER_HPP
#define COMMAND_MAPPER_HPP

#include <functional>
#include <string>
#include <unordered_map>

#include "command_executor.hpp"

class TFMCommandMapper {
   private:
    std::unordered_map<std::string, command_func> match_table;

   public:
    TFMCommandMapper() = default;
    ~TFMCommandMapper() = default;

    void register_command(const std::string& name, command_func func);
    std::unordered_map<std::string, command_func>::iterator find(
        const std::string& name);

    std::unordered_map<std::string, command_func>::iterator end();
};

#endif