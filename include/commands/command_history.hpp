#pragma once

#include <stack>
#include <stdexcept>
#include <string>
#include <vector>

class TFMCommandHistory {
   private:
    std::stack<std::vector<std::string>> m_previous_stack;
    std::stack<std::vector<std::string>> m_upcoming_stack;
    std::vector<std::string> m_last_entry;

   public:
    TFMCommandHistory() = default;
    ~TFMCommandHistory() = default;

    std::vector<std::string> get_last_entry() { return m_last_entry; }
    void set_last_entry(const std::vector<std::string>& last_entry) {
        m_last_entry = last_entry;
    }

    bool has_previous() const { return !m_previous_stack.empty(); }
    bool has_upcoming() const { return !m_upcoming_stack.empty(); }

    std::vector<std::string> display_previous();
    std::vector<std::string> display_upcoming();

    void add_previous(const std::vector<std::string>& command);
    void add_upcoming(const std::vector<std::string>& command);

    std::vector<std::string> pop_previous();
    std::vector<std::string> pop_upcoming();

    void undo();
    void redo();
    void clear();
};
