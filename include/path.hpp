#ifndef PATH_HPP
#define PATH_HPP

#include <filesystem>

namespace fs = std::filesystem;

class TFMPathHandler {
   private:
    fs::path m_path;

   public:
    TFMPathHandler() : m_path{fs::current_path()} {}
    ~TFMPathHandler() = default;

    fs::path get() const { return m_path; }
    void set(const fs::path& path) { m_path = path; }
};

#endif