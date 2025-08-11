#include "command_mapper.hpp"

#include "command_executor.hpp"

void TFMCommandMapper::register_command(const std::string& name,
                                        command_func func) {
    match_table[name] = func;
}

std::unordered_map<std::string, command_func>::iterator TFMCommandMapper::find(
    const std::string& name) {
    return match_table.find(name);
}

std::unordered_map<std::string, command_func>::iterator
TFMCommandMapper::end() {
    return match_table.end();
}