#pragma once

#include <functional>
#include <string>
#include <unordered_map>

#include "command_executor.hpp"

namespace TFM {

/**
 * @brief Holds the map of each command (string) to it's implementation (fn)
 *
 */
class CommandMapper {
   private:
    std::unordered_map<std::string, command_func> m_match_table;

   public:
    /**
     * @brief Construct a new CommandMapper object
     *
     */
    CommandMapper() = default;

    /**
     * @brief Destroy the CommandMapper object
     *
     */
    ~CommandMapper() = default;

    /**
     * @brief Registers a new command to be used
     *
     * @param name
     * @param func
     */
    void register_command(const std::string& name, command_func func);

    /**
     * @brief Tries to find an element inside the map
     *
     * @param name
     * @return std::unordered_map<std::string, command_func>::iterator
     */
    std::unordered_map<std::string, TFM::command_func>::iterator find(
        const std::string& name);

    /**
     * @brief Returns the map's end
     *
     * @return std::unordered_map<std::string, command_func>::iterator
     */
    std::unordered_map<std::string, TFM::command_func>::iterator end();
};

}  // namespace TFM
