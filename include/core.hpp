#include <string>
#ifndef CORE_HPP
#define CORE_HPP

#define CTRL_KEY(c) ((c) & 0x1f)

#define die(msg) (_die(__FILE__, __LINE__, msg))

void _die(const std::string& filename, int32_t line,
          const std::string& message);

#endif