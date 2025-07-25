#include "string_utils.hpp"

#include <cctype>

std::string trim(const std::string& str) {
    size_t start = 0;
    while (start < str.size() && std::isspace(static_cast<char>(str[start]))) {
        start++;
    }

    size_t end = str.size() - 1;

    while (end > start && std::isspace(static_cast<char>(str[end]))) {
        end--;
    }

    return str.substr(start, end - start + 1);
}