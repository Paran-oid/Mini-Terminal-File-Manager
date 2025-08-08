#include <string>
#ifndef CORE_HPP
#define CORE_HPP

#define CTRL_KEY(c) ((c) & 0x1f)

std::string ls_format(const std::string& dst, size_t spacing);
void str_replace_str_to_str(std::string& dst, const std::string& to_replace,
                            const std::string& replacement);

#endif