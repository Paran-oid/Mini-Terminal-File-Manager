#include "file.hpp"

#include <grp.h>
#include <pwd.h>
#include <sys/stat.h>

#include <array>
#include <cmath>
#include <cstdint>
#include <exception>
#include <filesystem>
#include <iostream>
#include <sstream>

namespace fs = std::filesystem;

TFM::File TFM::FileManager::file_init(const std::string& path) {
    if (!fs::exists(path)) {
        throw std::runtime_error("file with this path not found");
    }

    File f;

    fs::path p(path);
    f.name = p.filename().string();
    f.path = fs::absolute(p);
    f.size = fs::is_regular_file(path) ? fs::file_size(path) : 0;
    f.type = NO_FILE_DETECTED;

    struct stat st;
    if (!stat(f.path.c_str(), &st)) {
        if (S_ISCHR(st.st_mode)) {
            f.type = CHAR_DEVICE;
        } else if (S_ISBLK(st.st_mode)) {
            f.type = BLOCK_DEVICE;
        } else if (S_ISFIFO(st.st_mode)) {
            f.type = PIPE;
        }

        f.timestamps[0] = st.st_atim.tv_sec;
        f.timestamps[1] = st.st_mtim.tv_sec;
        f.timestamps[2] = st.st_ctim.tv_sec;

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

    if (f.type == NO_FILE_DETECTED) {
        if (fs::is_directory(p)) {
            f.type = DIRECTORY;
        } else if (fs::is_regular_file(p)) {
            f.type = REGULAR;
        } else if (fs::is_symlink(p)) {
            f.type = SYMLINK;
        } else {
            throw std::runtime_error(
                "no file type exists corresponding to this file...");
        }
    }

    return f;
}

std::string TFM::FileManager::str_representation_permissions(const File& file) {
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
        default:
            throw std::runtime_error(
                "no file type exists corresponding to this file...");
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

std::string TFM::FileManager::format_size_to_human_readable(size_t bytes) {
    const std::array<std::string, 5> size_units = {"", "KB", "MB", "GB", "TB"};

    double size = static_cast<double>(bytes);
    uint8_t index = 0;

    while (size >= 1024 && index < size_units.size() - 1) {
        size /= 1024;
        index++;
    }

    std::ostringstream os;
    os << std::fixed << std::setprecision(1) << size << " "
       << size_units[index];
    return os.str();
}

std::string TFM::FileManager::str_file_details(const File& file,
                                               bool human_readable) {
    std::ostringstream os;

    // format time
    time_t tim = file.timestamps[1];
    struct std::tm* lt = std::localtime(&tim);

    char buf[64];
    std::strftime(buf, sizeof(buf), "%b %e %H:%M", lt);

    const std::string formatted_time(buf);

    // get owner and group names
    struct stat st;
    stat(file.path.c_str(), &st);

    struct passwd* pw = getpwuid(file.uid);
    struct group* gr = getgrgid(file.gid);

    // clang-format off
	// [filetype][permissions] [num_links] [owner]  [group]  [size] [modification date] [filename]
    // clang-format on

    os << str_representation_permissions(file) << "  " << st.st_nlink << " "
       << pw->pw_name << "  " << gr->gr_name << "   "
       << (human_readable ? format_size_to_human_readable(file.size)
                          : std::to_string(file.size))
       << " " << formatted_time << " " << file.name;

    return os.str();
}
