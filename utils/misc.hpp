#ifndef MISC_HPP
#define MISC_HPP

#include <cstdint>
#include <iostream>
#include <string>

#define die(msg) (_die(msg, __FILE__, __LINE__))

inline void _die(const std::string& msg, const std::string& file,
                 int32_t line) {
    std::cerr << "[FATAL] " << msg << " at " << file << ":" << line
              << std::endl;
    std::exit(EXIT_FAILURE);
}

#endif