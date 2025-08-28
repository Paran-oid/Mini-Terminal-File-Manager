#pragma once

#include <string>
#include <vector>

namespace TFM {

/**
 * @brief Describes a command
 *
 */
struct Command {
    std::string name;                ///< name of the respective command
    std::vector<std::string> flags;  ///< any associated flags attached to it
    std::vector<std::string> positional;  ///< expected arguments
};

/**
 * @brief Handles parsing commands
 *
 */
class CommandParser {
   private:
   public:
    /**
     * @brief Construct a new CommandParser object
     *
     */
    CommandParser() = default;
    /**
     * @brief Destroy the CommandParser object
     *
     */
    ~CommandParser() = default;

    /**
     * @brief Returns a correctly formatted command
     *
     * @param command
     * @return Command
     */
    Command parse(const std::string& command) const;
};

}  // namespace TFM
