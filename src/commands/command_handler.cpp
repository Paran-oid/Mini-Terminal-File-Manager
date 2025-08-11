#include "command_handler.hpp"

#include <algorithm>
#include <cmath>
#include <core.hpp>
#include <cstdlib>
#include <filesystem>
#include <sstream>

#include "config.hpp"
#include "path.hpp"
#include "rows.hpp"
#include "screen.hpp"

namespace fs = std::filesystem;

void TFMCommandHandler::process(const std::string& input) {
    if (input.empty()) {
        return;
    }

    TFMCommand command = m_parser.parse(input);

    if (command.empty()) {
        return;
    }

    auto it = m_mapper.find(command.name);
    if (it != m_mapper.end()) {
        it->second(command);
    } else {
        m_executor.manage_error(command, INVALID);
    }
}
