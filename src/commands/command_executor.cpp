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

void TFMCommandExecutor::manage_error(const TFMCommand& cmd,
                                      TFMCommandErrorCode code,
                                      std::string data) {
    std::ostringstream message_buf;
    switch (code) {
        case INVALID_COMMAND:
            message_buf << cmd.name << ": cmd not found";
            break;
        case UNAVAILABLE_DIRECTORY:
            message_buf << cmd.name << ": " << cmd.args[0]
                        << ": no such file or directory";
            break;
        case MISSING_OPERAND:
            message_buf << cmd.name << ": " << "missing operand";
            break;
        case MISSING_FILE_OPERAND:
            if (cmd.args.empty()) {
                message_buf << cmd.name << ": " << "missing file operand";
            } else {
                message_buf << cmd.name << ": "
                            << "missing file operand after: '" << cmd.args[0]
                            << "'";
            }
            break;
        case MISSING_FILE_DESTINATION:
            message_buf << cmd.name << ": "
                        << "missing destination file operand after '"
                        << cmd.args[0] << "'";
            break;
        case FAILED_DIRECTORY_CREATION:
            if (data.empty()) {
                message_buf << cmd.name << ": " << "failed creating directory'";
            } else {
                message_buf << cmd.name << ": " << "failed creating directory '"
                            << data;
            }
            break;
        default:
            break;
    }

    m_rows.append(message_buf.str());
}

void TFMCommandExecutor::clear_func(const TFMCommand& cmd) {
    (void)cmd;
    m_rows.clear();
}

void TFMCommandExecutor::cd_func(const TFMCommand& cmd) {
    if (cmd.args.empty()) {
        return;
    }

    std::string path_str = cmd.args[0];
    m_path.expand(path_str);

    if (path_str == "-") {
        auto temp = m_path.get_path();
        path_str = m_path.get_previous_path().string();
        m_path.set_previous_path(temp);
    }

    fs::path target_path(path_str);

    if (!fs::exists(target_path)) {
        manage_error(cmd, UNAVAILABLE_DIRECTORY);
        return;
    }

    try {
        // handles symlinks and relative paths
        target_path = fs::canonical(target_path);
    } catch (const fs::filesystem_error& e) {
        manage_error(cmd, UNAVAILABLE_DIRECTORY);
        return;
    }

    m_path.set_previous_path(m_path.get_path());
    m_path.set_path(target_path);
}

void TFMCommandExecutor::ls_func(const TFMCommand& cmd) {
    (void)cmd;

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

void TFMCommandExecutor::pwd_func(const TFMCommand& cmd) {
    (void)cmd;
    m_rows.append(m_path.get_path().string());
}

void TFMCommandExecutor::whoami_func(const TFMCommand& cmd) {
    (void)cmd;
    m_rows.append(m_config.get_username());
}

// TODO: make cat func

void TFMCommandExecutor::cp_func(const TFMCommand& cmd) {
    (void)cmd;

    if (cmd.args.empty() || cmd.args.size() == 1) {
        manage_error(cmd, MISSING_FILE_OPERAND);
        return;
    }

    std::string src = cmd.args[0];
    std::string dst = cmd.args[1];
    if (!fs::exists(src)) {
        manage_error(cmd, MISSING_FILE_DESTINATION);
        return;
    }

    // !works just for files for now, until we introduce flags
    fs::copy(src, dst);
}

void TFMCommandExecutor::mkdir_func(const TFMCommand& cmd) {
    if (cmd.args.empty()) {
        manage_error(cmd, MISSING_OPERAND);
    }

    for (const auto& arg : cmd.args) {
        std::string str_path = m_path.get_path().string() + "/" + arg;
        try {
            fs::create_directories(str_path);
        } catch (const fs::filesystem_error& e) {
            manage_error(cmd, FAILED_DIRECTORY_CREATION, arg);
        }
    }
}