#pragma once

#include <cstdint>
#include <string>
#include <vector>

#define CTRL_KEY(c) ((c) & 0x1f)

std::string ls_format(const std::string& dst, size_t spacing);
void str_replace_str_to_str(std::string& dst, const std::string& to_replace,
                            const std::string& replacement);
uint32_t str_num_common_chars(const std::string& str1, const std::string& str2);
