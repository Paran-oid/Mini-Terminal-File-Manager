#include "command_executor.hpp"

#include <algorithm>
#include <chrono>
#include <cmath>
#include <fstream>
#include <sstream>

#include "command_parser.hpp"
#include "config.hpp"
#include "core.hpp"
#include "path.hpp"
#include "rows.hpp"
#include "screen.hpp"

// TODO: make sure all flags are written for each command

void TFMCommandExecutor::manage_error(const TFMCommand& cmd,
                                      TFMCommandErrorCode code,
                                      std::string data) {
    std::ostringstream message_buf;
    switch (code) {
        case INVALID_COMMAND:
            message_buf << cmd.name << ": cmd not found";
            break;
        case UNAVAILABLE_DIRECTORY:
            message_buf << cmd.name << ": " << cmd.positional[0]
                        << ": no such file or directory";
            break;
        case MISSING_OPERAND:
            message_buf << cmd.name << ": " << "missing operand";
            break;
        case MISSING_FILE_OPERAND:
            if (cmd.positional.empty()) {
                message_buf << cmd.name << ": " << "missing file operand";
            } else {
                message_buf << cmd.name << ": "
                            << "missing file operand after: '"
                            << cmd.positional[0] << "'";
            }
            break;
        case MISSING_FILE_DESTINATION:
            message_buf << cmd.name << ": "
                        << "missing destination file operand after '"
                        << cmd.positional[0] << "'";
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
    if (cmd.positional.empty()) {
        return;
    }

    std::string path_str = cmd.positional[0];
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

    // TODO: fix it sometimes not creating padding?
    bool show_hidden_files = false;
    // bool long_listing = false;
    // bool reverse_order = false;

    for (const std::string& arg : cmd.flags) {
        if (arg == "a") {
            show_hidden_files = true;
        }
        // } else if (arg == "l") {
        //     long_listing = true;
        // } else if (arg == "r") {
        //     reverse_order = true;
        // }
    }

    // TODO: make it check if there was a path entered else just process with ./

    // get all current files/folders
    std::vector<std::string> filenames;
    for (const auto& entry : fs::directory_iterator(m_path.get_path())) {
        std::string filename = entry.path().filename();
        if (!show_hidden_files && filename[0] == '.') {
            continue;
        }
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

    size_t cols = static_cast<size_t>(m_screen.get_cols() / max_length);
    size_t rows = static_cast<size_t>(std::ceil(
        static_cast<float>(filenames.size()) / static_cast<float>(cols)));

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

    if (cmd.positional.empty() || cmd.positional.size() == 1) {
        manage_error(cmd, MISSING_FILE_OPERAND);
        return;
    }

    bool is_recursive = false;

    // TODO: make this work
    for (const std::string& arg : cmd.flags) {
        if (arg == "r") {
            is_recursive = true;
        }
    }

    std::string src = cmd.positional[0];
    std::string dst = cmd.positional[1];
    if (!fs::exists(src)) {
        manage_error(cmd, MISSING_FILE_DESTINATION);
        return;
    }

    fs::copy(
        src, dst,
        is_recursive ? fs::copy_options::recursive : fs::copy_options::none);
}

void TFMCommandExecutor::mkdir_func(const TFMCommand& cmd) {
    if (cmd.positional.empty()) {
        manage_error(cmd, MISSING_OPERAND);
    }

    for (const auto& arg : cmd.positional) {
        std::string str_path = m_path.get_path().string() + "/" + arg;
        try {
            fs::create_directories(str_path);
        } catch (const fs::filesystem_error& e) {
            manage_error(cmd, FAILED_DIRECTORY_CREATION, arg);
        }
    }
}

void TFMCommandExecutor::touch_func(const TFMCommand& cmd) {
    if (cmd.positional.empty()) {
        manage_error(cmd, MISSING_FILE_OPERAND);
        return;
    }

    for (const std::string& arg : cmd.positional) {
        // ignore flags
        if (arg[0] == '-') {
            continue;
        }

        fs::path path = fs::path(arg);

        if (fs::exists(path)) {
            auto now = std::chrono::file_clock::now();
            fs::last_write_time(path, now);
        } else {
            std::ofstream ofs(path);
            ofs.close();
        }
    }
}