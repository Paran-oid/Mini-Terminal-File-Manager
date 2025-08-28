#include "command_handler.hpp"

#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <filesystem>
#include <sstream>
#include <utils.hpp>

#include "config.hpp"
#include "path.hpp"
#include "rows.hpp"
#include "screen.hpp"

namespace fs = std::filesystem;

void TFM::CommandHandler::process(const std::string& input) {
    if (input.empty()) {
        return;
    }

    TFM::Command cmd = m_parser.parse(input);

    if (cmd.name.empty()) {
        return;
    }

    auto it = m_mapper.find(cmd.name);
    if (it != m_mapper.end()) {
        it->second(cmd);
    } else {
        m_executor.manage_error(cmd, INVALID_COMMAND);
    }
}
