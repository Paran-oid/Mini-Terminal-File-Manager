#pragma once

#include <array>
#include <cstdint>
#include <string>
#include <vector>

// TODO: consider creating a namespace for everything related to TFM
// TODO: instead of TFMFile do TFM::File ie

namespace TFM {

/*

we want to make ls able to output something like this when specific flags are
entered

aziz@aziz-Vostro-3525:~/Documents/Coding/Projects/Software/Terminal File
Manager/build/test_dir$ ls -l
total 4
-rw-rw-r-- 1 aziz aziz    0 Aug 23 16:35 a
-rw-rw-r-- 1 aziz aziz    0 Aug 23 16:35 b
drwxrwxr-x 2 aziz aziz 4096 Aug 23 16:37 cool_dir
-rw-rw-r-- 1 aziz aziz    0 Aug 26 14:27 file.txt
aziz@aziz-Vostro-3525:~/Documents/Coding/Projects/Software/Terminal File
Manager/build/test_dir$


*/

#define READ_FLAG(perm) (((perm) >> 2) & 0x01)
#define WRITE_FLAG(perm) (((perm) >> 1) & 0x01)
#define EXECUTE_FLAG(perm) (((perm) >> 0) & 0x01)

enum FileType {
    NONE,
    DIRECTORY,
    REGULAR,
    SYMLINK,
    PIPE,
    BLOCK_DEVICE,
    CHAR_DEVICE,
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
};

}  // namespace TFM
