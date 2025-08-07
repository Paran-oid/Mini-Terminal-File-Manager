#include "command_handler.hpp"

#include <algorithm>
#include <core.hpp>
#include <cstdlib>
#include <filesystem>
#include <sstream>

#include "path.hpp"
#include "rows.hpp"
#include "screen.hpp"

namespace fs = std::filesystem;

void TFMCommandHandler::manage_error(const std::vector<std::string>& args,
                                     TFMCommandErrorCode code) {
    (void)args;
    std::ostringstream message_buf;
    switch (code) {
        case INVALID:
            message_buf << args[0] << ": command not found";
            break;
        case UNAVAILABLE_DIRECTORY:
            message_buf << args[0] << ": " << args[1]
                        << ": no such file or directory";
            break;
        default:
            break;
    }

    message_buf << '\n';
    m_rows.append(message_buf.str());
}

void TFMCommandHandler::clear_func(const std::vector<std::string>& args) {
    (void)args;
    m_rows.clear();
}

void TFMCommandHandler::cd_func(const std::vector<std::string>& args) {
    if (args.empty()) {
        return;
    }

    std::string path_str = args[1];
    if (!fs::exists(path_str)) {
        manage_error(args, UNAVAILABLE_DIRECTORY);
        return;
    }

    // TODO: fix it not being able to enter a directory by name

    fs::path path = fs::path(path_str);
    if (path.is_relative()) {
        // expands to absolute path
        path = fs::canonical(path);
    } else if (path == "-") {
        // TODO: to implement
    } else if (path_str.contains("~")) {
        // TODO: to implement
    }
    path_str = path.string();
    m_path.set(path);
}

void TFMCommandHandler::ls_func(const std::vector<std::string>& args) {
    (void)args;
    // get all current files/folders
    std::vector<std::string> filenames;
    for (const auto& entry : fs::directory_iterator(m_path.get())) {
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
    size_t rows = filenames.size() / cols;

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
        m_rows.append(os.str() + "\n");
    }
}
void TFMCommandHandler::pwd_func(const std::vector<std::string>& args) {
    (void)args;
    m_rows.append(m_path.get().string() + '\n');
}

void TFMCommandHandler::match_table_init() {
    match_table["cd"] = [this](const std::vector<std::string>& args) {
        this->cd_func(args);
    };
    match_table["ls"] = [this](const std::vector<std::string>& args) {
        this->ls_func(args);
    };
    match_table["pwd"] = [this](const std::vector<std::string>& args) {
        this->pwd_func(args);
    };

    // TODO: fix me
    match_table["clear"] = [this](const std::vector<std::string>& args) {
        this->clear_func(args);
    };
}

std::vector<std::string> TFMCommandHandler::parse(const std::string& command) {
    std::vector<std::string> res;

    std::istringstream iss(command);
    std::string buf;
    while (iss >> buf) {
        res.push_back(buf);
    }

    return res;
}

void TFMCommandHandler::process(const std::string& command) {
    if (command.empty()) {
        return;
    }

    m_args = this->parse(command);

    if (m_args.empty() || !match_table.contains(m_args[0])) {
        manage_error(m_args, INVALID);
    } else {
        match_table[m_args[0]](m_args);
    }
}