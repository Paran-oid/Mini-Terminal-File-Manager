#pragma once

#include <stack>
#include <stdexcept>
#include <string>
#include <vector>

/**
 * @brief Handles command history (particularily useful when user pressed either
 * arrow up or arrow down)
 *
 */
class TFMCommandHistory {
   private:
    std::stack<std::vector<std::string>> m_previous_stack;
    std::stack<std::vector<std::string>> m_upcoming_stack;
    std::vector<std::string> m_last_entry;

   public:
    /**
     * @brief Construct a new TFMCommandHistory object
     *
     */
    TFMCommandHistory() = default;

    /**
     * @brief Destroy the TFMCommandHistory object
     *
     */
    ~TFMCommandHistory() = default;

    /**
     * @brief Get the last entry object
     *
     * @return std::vector<std::string>
     */
    std::vector<std::string> get_last_entry() { return m_last_entry; }

    /**
     * @brief Set the last entry object
     *
     * @param last_entry
     */
    void set_last_entry(const std::vector<std::string>& last_entry) {
        m_last_entry = last_entry;
    }

    /**
     * @brief Checks if there is a previos command
     *
     * @return true
     * @return false
     */
    bool has_previous() const { return !m_previous_stack.empty(); }

    /**
     * @brief Checks if there is an upcoming command
     *
     * @return true
     * @return false
     */
    bool has_upcoming() const { return !m_upcoming_stack.empty(); }

    /**
     * @brief Displays previous command (if there is any)
     *
     * @return std::vector<std::string>
     */
    std::vector<std::string> display_previous();

    /**
     * @brief Displays upcoming command (if there is any)
     *
     * @return std::vector<std::string>
     */
    std::vector<std::string> display_upcoming();

    /**
     * @brief Adds a new command to previous container
     *
     * @param command
     */
    void add_previous(const std::vector<std::string>& command);

    /**
     * @brief Adds a new command to upcoming container
     *
     * @param command
     */
    void add_upcoming(const std::vector<std::string>& command);

    /**
     * @brief Pops last element in previous container
     *
     * @return std::vector<std::string>
     */
    std::vector<std::string> pop_previous();

    /**
     * @brief Pops last element in upcoming container
     *
     * @return std::vector<std::string>
     */
    std::vector<std::string> pop_upcoming();

    /**
     * @brief Undos last change
     *
     */
    void undo();

    /**
     * @brief Redos last change
     *
     */
    void redo();

    /**
     * @brief Clears history
     *
     */
    void clear();
};
