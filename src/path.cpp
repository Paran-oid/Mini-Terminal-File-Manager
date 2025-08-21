#include "path.hpp"

#include <unistd.h>

#include <algorithm>
#include <stdexcept>
#include <unordered_map>

#include "utils.hpp"

void TFMPathHandler::set_path(const fs::path& path) {
    m_current_path = path;

    const char* path_c_str = path.c_str();
    if (chdir(path_c_str) != 0) {
        throw std::runtime_error("Changing directory failed...");
    }
}

void TFMPathHandler::update_home_dir() {
    const std::string& path = m_current_path.string();

    uint8_t counter = 0;
    auto it = std::find_if(path.begin(), path.end(), [&counter](char c) {
        if (c == '/') {
            counter++;
        }
        if (counter == 3) {
            return true;
        } else {
            return false;
        }
    });

    if (it == path.end()) {
        throw std::runtime_error("Invalid path passed");
    }

    m_home_dir =
        path.substr(0, static_cast<size_t>(std::distance(path.begin(), it)));
}

void TFMPathHandler::expand(std::string& path) {
    if (path[0] != '~' || std::count(path.begin(), path.end(), '~') > 1) {
        return;
    }

    str_replace_str_to_str(path, "~", m_home_dir);
}
