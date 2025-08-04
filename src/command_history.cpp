#include "command_history.hpp"

std::vector<std::string> TFMCommandHistory::pop_previous() {
    if (!has_previous()) return {};
    std::vector<std::string> res = m_previous_stack.top();
    m_previous_stack.pop();
    return res;
}

std::vector<std::string> TFMCommandHistory::pop_upcoming() {
    if (!has_upcoming()) return {};
    std::vector<std::string> res = m_upcoming_stack.top();
    m_upcoming_stack.pop();
    return res;
}

void TFMCommandHistory::add_previous(const std::vector<std::string>& command) {
    m_previous_stack.push(command);
}

void TFMCommandHistory::add_upcoming(const std::vector<std::string>& command) {
    m_upcoming_stack.push(command);
}

void TFMCommandHistory::undo() {
    if (!has_previous()) return;
    std::vector<std::string> prev = pop_previous();
    add_upcoming(prev);
}
void TFMCommandHistory::redo() {
    if (!has_upcoming()) {
        add_upcoming(m_last_entry);
    }
    std::vector<std::string> next = pop_upcoming();
    add_previous(next);
}
void TFMCommandHistory::clear() {
    while (!m_upcoming_stack.empty()) m_upcoming_stack.pop();
    while (!m_previous_stack.empty()) m_previous_stack.pop();
}

std::vector<std::string> TFMCommandHistory::display_previous() {
    return has_previous() ? m_previous_stack.top() : std::vector<std::string>();
}

std::vector<std::string> TFMCommandHistory::display_upcoming() {
    return has_upcoming() ? m_upcoming_stack.top() : std::vector<std::string>();
}
