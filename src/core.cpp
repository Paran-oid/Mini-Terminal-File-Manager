#include "core.hpp"

#include <ncurses.h>

#include <sstream>

std::string ls_format(const std::string& dst, size_t spacing) {
    if (spacing <= dst.length()) return dst;
    std::string res = dst + std::string(spacing - dst.length(), ' ');
    return res;
}

void str_replace_str_to_str(std::string& dst, const std::string& to_replace,
                            const std::string& replacement) {
    size_t index = dst.find(to_replace);
    if (index == std::string::npos) return;

    std::ostringstream os;
    os << dst.substr(0, index);
    os << replacement;
    os << dst.substr(index + 1);

    dst = os.str();
}
