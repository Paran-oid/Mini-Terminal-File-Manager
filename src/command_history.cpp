#include "command_history.hpp"

std::string TFMCommandHistory::pop_previous() {
    if (!has_previous()) return "";
    std::string res = previous_stack.top();
    previous_stack.pop();
    return res;
}

std::string TFMCommandHistory::pop_upcoming() {
    if (!has_upcoming()) return "";
    std::string res = upcoming_stack.top();
    upcoming_stack.pop();
    return res;
}

void TFMCommandHistory::add_previous(const std::string& command) {
    previous_stack.push(command);
}

void TFMCommandHistory::add_upcoming(const std::string& command) {
    upcoming_stack.push(command);
}

void TFMCommandHistory::undo() {
    if (!has_previous()) return;
    std::string prev = pop_previous();
    add_upcoming(prev);
}
void TFMCommandHistory::redo() {
    if (!has_upcoming()) return;
    std::string next = pop_upcoming();
    add_previous(next);
}
void TFMCommandHistory::clear() {
    while (!upcoming_stack.empty()) upcoming_stack.pop();
    while (!previous_stack.empty()) previous_stack.pop();
}

std::string TFMCommandHistory::display_previous() {
    return has_previous() ? previous_stack.top() : "";
}

std::string TFMCommandHistory::display_upcoming() {
    return has_upcoming() ? upcoming_stack.top() : "";
}
