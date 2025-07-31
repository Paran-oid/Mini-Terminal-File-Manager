#ifndef PATH_HPP
#define PATH_HPP

#include <filesystem>

class TFMPathHandler {
   private:
    std::filesystem::path m_path;

   public:
    TFMPathHandler() : m_path{std::filesystem::current_path()} {}
    ~TFMPathHandler() = default;

    std::filesystem::path get() const { return m_path; }
    void set(const std::filesystem::path& path) { m_path = path; }
};

#endif