#pragma once

#include <string>
#include <vector>

namespace TFM {

struct CommandToken {
    std::string name;
    size_t index;
};

/**
 * @brief Describes a command
 *
 */
struct Command {
    std::string name;                       ///< name of the respective command
    std::vector<CommandToken> short_flags;  ///< short flags like -a
    std::vector<CommandToken> long_flags;   ///< long flags like --help
    std::vector<CommandToken> positional;   ///< expected arguments
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
