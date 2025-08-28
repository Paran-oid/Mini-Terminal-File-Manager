#include "command_history.hpp"

std::vector<std::string> TFM::CommandHistory::display_previous() {
    return has_previous() ? m_previous_stack.top() : std::vector<std::string>();
}

std::vector<std::string> TFM::CommandHistory::display_upcoming() {
    return has_upcoming() ? m_upcoming_stack.top() : std::vector<std::string>();
}

void TFM::CommandHistory::add_previous(const std::vector<std::string>& cmd) {
    m_previous_stack.push(cmd);
}

void TFM::CommandHistory::add_upcoming(const std::vector<std::string>& cmd) {
    m_upcoming_stack.push(cmd);
}

std::vector<std::string> TFM::CommandHistory::pop_previous() {
    if (!has_previous()) return {};
    std::vector<std::string> res = m_previous_stack.top();
    m_previous_stack.pop();
    return res;
}

std::vector<std::string> TFM::CommandHistory::pop_upcoming() {
    if (!has_upcoming()) return {};
    std::vector<std::string> res = m_upcoming_stack.top();
    m_upcoming_stack.pop();
    return res;
}

void TFM::CommandHistory::undo() {
    if (!has_previous()) return;
    std::vector<std::string> prev = pop_previous();
    add_upcoming(prev);
}
void TFM::CommandHistory::redo() {
    if (!has_upcoming()) {
        add_upcoming(m_last_entry);
    }
    std::vector<std::string> next = pop_upcoming();
    add_previous(next);
}
void TFM::CommandHistory::clear() {
    while (!m_upcoming_stack.empty()) m_upcoming_stack.pop();
    while (!m_previous_stack.empty()) m_previous_stack.pop();
}
