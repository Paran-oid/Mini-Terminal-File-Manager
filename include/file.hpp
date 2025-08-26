#pragma once

#include <array>
#include <cstdint>
#include <string>

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

enum FileType { DIRECTORY, REGULAR, SYMLINK, PIPE, BLOCK_DEVICE, CHAR_DEVICE };
enum FilePermissions { READ = 4, WRITE = 2, EXECUTE = 1 };

struct File {
    std::string name;
    std::string path;
    size_t size;

    FileType type;

    std::array<timespec, 3> timestamps;
    std::array<uint8_t, 3> permissions;

    uid_t uid;
    gid_t gid;
};

class FileManager {
   private:
   public:
    FileManager(){};
    ~FileManager(){};

    File file_init(const std::string& path);

    std::string FileManager::str_representation_permissions(const File& file);
    std::string str_human_readable_size(const File& file);
};

}  // namespace TFM
