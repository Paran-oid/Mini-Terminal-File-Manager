#pragma once

#include <array>
#include <cstdint>
#include <filesystem>
#include <string>
#include <vector>

namespace fs = std::filesystem;

namespace TFM {

#define READ_FLAG(perm) (((perm) >> 2) & 0x01)
#define WRITE_FLAG(perm) (((perm) >> 1) & 0x01)
#define EXECUTE_FLAG(perm) (((perm) >> 0) & 0x01)

enum FileType {
    DIRECTORY,
    REGULAR,
    SYMLINK,
    PIPE,
    BLOCK_DEVICE,
    CHAR_DEVICE,
    NO_FILE_DETECTED
};
enum FilePermissions { READ = 4, WRITE = 2, EXECUTE = 1 };

/**
 * @brief Structure to hold file metada
 *
 */
struct File {
    std::string name;  ///< filename
    std::string path;  ///< absolute path
    size_t size;       ///< size in bytes

    FileType type;  ///< regular, symlink, pipe, ...

    std::array<time_t, 3>
        timestamps;  ///< [access a, modification m, creation c]

    std::array<uint8_t, 3> permissions;  ///< [owner, group, others]

    uid_t uid;  ///< owner id
    gid_t gid;  ///< group id
};

// TODO: make anything related to printing a file or handling a file in general
// TODO: use this class

// TODO: make it count size of a directory recursively through all it's files
// TODO: and subdirs

/**
 * @brief Manages any file passed
 * (Follows a Manager/Repository design pattern)
 * Data Object is considered File here
 *
 */
class FileManager {
   private:
    std::string str_representation_permissions(const File& file);
    std::string format_size_to_human_readable(size_t bytes);

   public:
    /**
     * @brief Construct a new File Manager object
     *
     */
    FileManager(){};

    /**
     * @brief Destroy the File Manager object
     *
     */
    ~FileManager(){};

    /**
     * @brief initializes file structure with just path
     *
     * @param path
     * @return File
     */
    File file_init(const std::string& path);

    /**
     * @brief formats file details in a ls -l style
     *
     * @param file
     * @param flags
     * @return std::string
     */
    std::string str_file_details(const File& file, bool human_readable);
    size_t file_dir_size(const fs::path& path);
    size_t total_blocks(const fs::path& path);
};

}  // namespace TFM
