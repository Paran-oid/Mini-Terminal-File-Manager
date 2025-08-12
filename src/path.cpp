#include "path.hpp"

#include <unistd.h>

#include <algorithm>
#include <stdexcept>
#include <unordered_map>

#include "core.hpp"

void TFMPathHandler::set_path(const fs::path& path) {
    m_current_path = path;

    const char* path_c_str = path.c_str();
    if (chdir(path_c_str) != 0) {
        throw std::runtime_error("Changing directory failed...");
    }
}

void TFMPathHandler::expand(std::string& path) {
    if (path[0] != '~' || std::count(path.begin(), path.end(), '~') > 1) {
        return;
    }

    str_replace_str_to_str(path, "~", m_home_dir);
}

void TFMPathHandler::update_home_dir() {
    std::string path = m_current_path.string();

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

std::vector<std::string> TFMPathHandler::find_matches(const std::string& row) {
    if (row.empty()) return {};

    std::vector<std::string> filenames, matches;
    for (auto& entry : fs::directory_iterator(this->get_path())) {
        filenames.push_back(entry.path().filename().string());
    }

    std::copy_if(filenames.begin(), filenames.end(),
                 std::back_inserter(matches),
                 [&row](const std::string& filename) {
                     return str_num_common_chars(row, filename) > 0;
                 });

    return matches;
}

std::string TFMPathHandler::find_best_match(const std::string& row) {
    // TODO: try to find in list of commands


    // !if not found in list of commands try to find matching directory
    std::vector<std::string> matches = this->find_matches(row);

    if (matches.empty()) {
        return row;
    }

    std::unordered_map<std::string, uint32_t> match_map;

    for (const auto& match : matches) {
        match_map[match] = str_num_common_chars(row, match);
    }

    auto max_it = std::max_element(
        match_map.begin(), match_map.end(),
        [](const auto& a, const auto& b) { return a.second < b.second; });

    if (max_it == match_map.end()) {
        // map is empty???
        return row;
    }

    auto count_max = std::count_if(
        match_map.begin(), match_map.end(),
        [&max_it](const auto& item) { return item.second == max_it->second; });

    if (count_max > 1) {
        return row;
    }

    return max_it->first;
}