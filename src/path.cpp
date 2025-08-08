#include "path.hpp"

#include <unistd.h>

#include <stdexcept>

void TFMPathHandler::set(const fs::path& path) {
    m_path = path;

    const char* path_c_str = path.c_str();
    if (chdir(path_c_str) != 0) {
        throw std::runtime_error("Changing directory failed...");
    }
}