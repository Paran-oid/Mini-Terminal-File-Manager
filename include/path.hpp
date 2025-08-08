#ifndef PATH_HPP
#define PATH_HPP

#include <filesystem>

namespace fs = std::filesystem;

class TFMPathHandler {
   private:
    fs::path m_current_path;
    fs::path m_previous_path;

    std::string m_home_dir;

   public:
    TFMPathHandler() : m_current_path{fs::current_path()} { update_home_dir(); }
    ~TFMPathHandler() = default;

    fs::path get_path() const { return m_current_path; }
    void set_path(const fs::path& path);

    fs::path get_previous_path() const {
        if (m_previous_path.empty()) return m_current_path;
        return m_previous_path;
    }
    void set_previous_path(const fs::path& previous_path) {
        m_previous_path = previous_path;
    }

    void update_home_dir();
    void expand(std::string& path);
};

#endif