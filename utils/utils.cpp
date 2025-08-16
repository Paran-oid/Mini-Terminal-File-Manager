#include "utils.hpp"

#include <ncurses.h>

#include <algorithm>
#include <sstream>
#include <vector>

std::string ls_format(const std::string& dst, size_t spacing) {
    if (spacing <= dst.length()) return dst;
    std::string res = dst + std::string(spacing - dst.length() + 1, ' ');
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

uint32_t str_num_common_chars(const std::string& str1,
                              const std::string& str2) {
    uint32_t res = 0;
    for (size_t i = 0; i < str1.size() && i < str2.size(); i++) {
        if (str1[i] == str2[i]) {
            res++;
        }
    }
    return res;
}
bool is_seperator(char c) {
    std::string separators = "!\"#$%&\'()*+,-./:;<=>?@[\\]^`{|}~";
    return separators.find(c) != std::string::npos || c == ' ';
}
