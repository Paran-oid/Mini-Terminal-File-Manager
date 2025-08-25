#pragma once

#include <string>
#include <vector>

/**
 * @brief Describes a command
 *
 */
struct TFMCommand {
    std::string name;                ///< name of the respective command
    std::vector<std::string> flags;  ///< any associated flags attached to it
    std::vector<std::string> positional;  ///< expected arguments
};

/**
 * @brief Handles parsing commands
 *
 */
class TFMCommandParser {
   private:
   public:
    /**
     * @brief Construct a new TFMCommandParser object
     *
     */
    TFMCommandParser() = default;
    /**
     * @brief Destroy the TFMCommandParser object
     *
     */
    ~TFMCommandParser() = default;

    /**
     * @brief Returns a correctly formatted command
     *
     * @param command
     * @return TFMCommand
     */
    TFMCommand parse(const std::string& command) const;
};
