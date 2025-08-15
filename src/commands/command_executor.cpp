#include "command_executor.hpp"

#include <algorithm>
#include <chrono>
#include <cmath>
#include <fstream>
#include <sstream>

#include "command_parser.hpp"
#include "config.hpp"
#include "path.hpp"
#include "rows.hpp"
#include "screen.hpp"
#include "utils.hpp"

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

// TODO: make sure all flags are written for each command

void TFMCommandExecutor::ls_func(const TFMCommand& cmd) {
    // handle flags
    bool show_hidden_files = false;
    for (const std::string& arg : cmd.flags) {
        if (arg == "a") {
            show_hidden_files = true;
        }
    }

    // initialize the map
    bool single_path = false;
    std::unordered_map<std::string, std::vector<std::string>> path_file_map;
    if (cmd.positional.empty()) {
        path_file_map[m_path.get_path()];
        single_path = true;
    } else {
        for (const std::string& arg : cmd.positional) {
            path_file_map[arg];
        }
    }

    // get all current files/folders
    for (auto& path_file : path_file_map) {
        const std::string& path = path_file.first;
        if (fs::is_regular_file(path)) {
            path_file.second.push_back(path_file.first);
            continue;
        }

        for (const auto& entry : fs::directory_iterator(path)) {
            std::string filename = entry.path().filename();
            if (!show_hidden_files && filename[0] == '.') {
                continue;
            }
            path_file.second.push_back(entry.path().filename().string());
        }
    }

    // order the vectors of each path
    for (auto& path_file : path_file_map) {
        std::sort(
            path_file.second.begin(), path_file.second.end(),
            [](const std::string& a, const std::string& b) { return a < b; });
    }

    // get longest length (we will get pair iterator returned)
    auto it_max_length =
        std::max_element(path_file_map.begin(), path_file_map.end(),
                         [](const auto& a, const auto& b) {
                             return a.second.size() < b.second.size();
                         });

    if (it_max_length == path_file_map.end()) {
        return;
    }

    size_t max_length = it_max_length->second.size();
    size_t cols = static_cast<size_t>(m_screen.get_cols() / max_length);

    for (const auto& [path, filenames] : path_file_map) {
        size_t rows = static_cast<size_t>(std::ceil(
            static_cast<float>(filenames.size()) / static_cast<float>(cols)));
        bool is_file_path = path == filenames[0] && filenames.size() == 1;
        std::ostringstream os;

        if (!single_path) {
            os << path;

            if (is_file_path) {
                os << ":";
                os << "\n";
            }

            os << "\n";
        }

        for (size_t i = 0; i < rows; i++) {
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
}

void TFMCommandExecutor::pwd_func(const TFMCommand& cmd) {
    (void)cmd;
    m_rows.append(m_path.get_path().string());
}

void TFMCommandExecutor::whoami_func(const TFMCommand& cmd) {
    (void)cmd;
    m_rows.append(m_config.get_username());
}

void TFMCommandExecutor::cat_func(const TFMCommand& cmd) {
    (void)cmd;
    // TODO
}

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

void TFMCommandExecutor::manage_error(const TFMCommand& cmd,
                                      TFMCommandErrorCode code,
                                      std::string data) {
    std::ostringstream message_buf;
    switch (code) {
        case INVALID_COMMAND:
            message_buf << cmd.name << ": command not found";
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