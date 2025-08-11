#include "command_executor.hpp"

#include <algorithm>
#include <cmath>
#include <sstream>

#include "command_parser.hpp"
#include "config.hpp"
#include "core.hpp"
#include "path.hpp"
#include "rows.hpp"
#include "screen.hpp"

void TFMCommandExecutor::manage_error(const TFMCommand& command,
                                      TFMCommandErrorCode code) {
    std::ostringstream message_buf;
    switch (code) {
        case INVALID:
            message_buf << command.name << ": command not found";
            break;
        case UNAVAILABLE_DIRECTORY:
            message_buf << command.name << ": " << command.args[0]
                        << ": no such file or directory";
            break;
        default:
            break;
    }

    m_rows.append(message_buf.str());
}

void TFMCommandExecutor::clear_func(const TFMCommand& command) {
    (void)command;
    m_rows.clear();
}

void TFMCommandExecutor::cd_func(const TFMCommand& command) {
    if (command.args.empty() || command.args.size() < 2) {
        return;
    }

    std::string path_str = command.args[1];
    m_path.expand(path_str);

    if (path_str == "-") {
        auto temp = m_path.get_path();
        path_str = m_path.get_previous_path().string();
        m_path.set_previous_path(temp);
    }

    fs::path target_path(path_str);

    if (!fs::exists(target_path)) {
        manage_error(command, UNAVAILABLE_DIRECTORY);
        return;
    }

    try {
        // handles symlinks and relative paths
        target_path = fs::canonical(target_path);
    } catch (const fs::filesystem_error& e) {
        manage_error(command, UNAVAILABLE_DIRECTORY);
        return;
    }

    m_path.set_previous_path(m_path.get_path());
    m_path.set_path(target_path);
}

void TFMCommandExecutor::ls_func(const TFMCommand& command) {
    (void)command;

    // TODO:
    // make a ls_analyze funciton to analyze for flags
    /*
            *	make enum for the flags (ask chatgpt to show you all for ls)
            *	ls_analyze returns num that has flags set
            *	ls_func handles them accordingly

    */

    // get all current files/folders
    std::vector<std::string> filenames;
    for (const auto& entry : fs::directory_iterator(m_path.get_path())) {
        filenames.push_back(entry.path().filename().string());
    }

    std::sort(filenames.begin(), filenames.end(),
              [](const std::string& a, const std::string& b) { return a < b; });

    // get longest length
    auto it_max_length =
        std::max_element(filenames.begin(), filenames.end(),
                         [](const std::string& a, const std::string& b) {
                             return a.size() < b.size();
                         });

    if (it_max_length == filenames.end()) {
        return;
    }

    size_t max_length = it_max_length->length();

    size_t cols = static_cast<size_t>(m_screen.get_cols()) / max_length;
    size_t rows = static_cast<size_t>(std::ceil(
        static_cast<double>(filenames.size()) / static_cast<double>(cols)));

    for (size_t i = 0; i < rows; i++) {
        std::ostringstream os;
        for (size_t j = 0; j < cols; j++) {
            size_t calculated_index = j * rows + i;

            if (calculated_index >= filenames.size()) {
                continue;
            }

            std::string filename =
                ls_format(filenames[calculated_index], max_length);
            os << filename;
        }
        m_rows.append(os.str());
        os.clear();
    }
}

void TFMCommandExecutor::pwd_func(const TFMCommand& command) {
    (void)command;
    m_rows.append(m_path.get_path().string());
}

void TFMCommandExecutor::whoami_func(const TFMCommand& command) {
    (void)command;
    m_rows.append(m_config.get_username());
}