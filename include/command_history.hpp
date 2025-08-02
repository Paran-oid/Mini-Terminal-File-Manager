#ifndef COMMAND_HISTORY_HPP
#define COMMAND_HISTORY_HPP

#include <stack>
#include <stdexcept>
#include <string>

class TFMCommandHistory {
   private:
    std::stack<std::string> previous_stack;
    std::stack<std::string> upcoming_stack;

    std::string pop_previous();
    std::string pop_upcoming();

   public:
    TFMCommandHistory() = default;
    ~TFMCommandHistory() = default;

    void add_previous(const std::string& command);
    void add_upcoming(const std::string& command);

    void undo();
    void redo();
    void clear();

    std::string display_previous();
    std::string display_upcoming();

    bool has_previous() const { return !previous_stack.empty(); }
    bool has_upcoming() const { return !upcoming_stack.empty(); }
};

#endif
