#pragma once

#include <filesystem>
#include <vector>

namespace fs = std::filesystem;

/**
 * @brief Responsible for Path handling
 *
 */
class TFMPathHandler {
   private:
    fs::path m_current_path;
    fs::path m_previous_path;

    std::string m_home_dir;

   public:
    /**
     * @brief Construct a new TFMPathHandler object
     *
     */
    TFMPathHandler() : m_current_path{fs::current_path()} { update_home_dir(); }

    /**
     * @brief Destroy the TFMPathHandler object
     *
     */
    ~TFMPathHandler() = default;

    /**
     * @brief Get the path object
     *
     * @return fs::path
     */
    fs::path get_path() const { return m_current_path; }

    /**
     * @brief Set the path object
     *
     * @param path
     */
    void set_path(const fs::path& path);

    /**
     * @brief Get the previous path object
     *
     * @return fs::path
     */
    fs::path get_previous_path() const {
        if (m_previous_path.empty()) return m_current_path;
        return m_previous_path;
    }

    /**
     * @brief Set the previous path object
     *
     * @param previous_path
     */
    void set_previous_path(const fs::path& previous_path) {
        m_previous_path = previous_path;
    }

    /**
     * @brief Updates the home dir using m_current_path
     *
     */
    void update_home_dir();

    /**
     * @brief Expands ~ with home_dir
     *
     * @param path
     */
    void expand(std::string& path);
};
