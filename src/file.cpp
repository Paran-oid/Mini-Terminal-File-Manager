#include "file.hpp"

#include <sys/stat.h>

#include <array>
#include <cstdint>
#include <exception>
#include <filesystem>
#include <iostream>
#include <sstream>

namespace fs = std::filesystem;

namespace TFM {

File FileManager::file_init(const std::string& path) {
    if (!fs::exists(path)) {
        throw std::runtime_error("file with this path not found");
    }

    File f;

    fs::path p(path);
    f.name = p.filename().string();
    f.path = fs::absolute(p);
    f.size = fs::is_regular_file(path) ? fs::file_size(path) : 0;

    struct stat st;
    if (!stat(f.path.c_str(), &st)) {
        if (S_ISCHR(st.st_mode)) {
            f.type = CHAR_DEVICE;
        } else if (S_ISBLK(st.st_mode)) {
            f.type = BLOCK_DEVICE;
        } else if (S_ISFIFO(st.st_mode)) {
            f.type = PIPE;
        }

        f.timestamps[0] = st.st_atim;
        f.timestamps[1] = st.st_mtim;
        f.timestamps[2] = st.st_ctim;

        f.uid = st.st_uid;
        f.gid = st.st_gid;

        /*
        Owner   Group   Others
        r w x   r w x   r w x
        8 7 6   5 4 3   2 1 0

        We need to shift!
        */

        f.permissions[0] = ((st.st_mode & S_IRWXU) >> 6);
        f.permissions[1] = ((st.st_mode & S_IRWXG) >> 3);
        f.permissions[2] = (st.st_mode & S_IRWXO);
    } else {
        throw std::runtime_error("stat init failed");
    }

    if (!f.type) {
        if (fs::is_directory(p)) {
            f.type = DIRECTORY;
        } else if (fs::is_regular_file(p)) {
            f.type = REGULAR;
        } else if (fs::is_symlink(p)) {
            f.type = SYMLINK;
        }
    }

    return f;
}

std::string FileManager::str_representation_permissions(const File& file) {
    std::ostringstream os;

    switch (file.type) {
        case REGULAR:
            os << '-';
            break;
        case DIRECTORY:
            os << 'd';
            break;
        case SYMLINK:
            os << 'l';
            break;
        case PIPE:
            os << 'p';
            break;
        case CHAR_DEVICE:
            os << 'c';
            break;
        case BLOCK_DEVICE:
            os << 'b';
            break;
    }

    for (uint8_t perm : file.permissions) {
        if (READ_FLAG(perm)) {
            os << 'r';
        } else {
            os << '-';
        }

        if (WRITE_FLAG(perm)) {
            os << 'w';
        } else {
            os << '-';
        }

        if (EXECUTE_FLAG(perm)) {
            os << 'x';
        } else {
            os << '-';
        }
    }

    return os.str();
}

std::string FileManager::str_human_readable_size(const File& file) {}

}  // namespace TFM