#include "command_mapper.hpp"

#include "command_executor.hpp"

void TFM::CommandMapper::register_command(const std::string& name,
                                          command_func func) {
    m_match_table[name] = func;
}

std::unordered_map<std::string, TFM::command_func>::iterator
TFM::CommandMapper::find(const std::string& name) {
    return m_match_table.find(name);
}

std::unordered_map<std::string, TFM::command_func>::iterator
TFM::CommandMapper::end() {
    return m_match_table.end();
}