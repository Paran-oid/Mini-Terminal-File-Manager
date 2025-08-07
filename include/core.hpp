#include <string>
#ifndef CORE_HPP
#define CORE_HPP

#define CTRL_KEY(c) ((c) & 0x1f)

std::string ls_format(const std::string& str, size_t spacing);

#endif