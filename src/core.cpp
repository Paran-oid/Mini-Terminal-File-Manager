#include "core.hpp"

#include <ncurses.h>

std::string ls_format(const std::string& str, size_t spacing) {
    if (spacing <= str.length()) return str;
    std::string res = str + std::string(spacing - str.length(), ' ');
    return res;
}