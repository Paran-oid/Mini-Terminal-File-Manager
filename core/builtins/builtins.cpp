#include "builtins.hpp"

#include <ncurses.h>

#include "context.hpp"

std::unordered_map<std::string, BuiltinFunc> builtin_commands;

void builtin_cd(TFM_Context& context, std::string& args) {
    if (args.empty()) {
        printw("No path entered\n");
    }
}
void builtin_ls(TFM_Context& context, std::string& args) {}
void builtin_exit(TFM_Context& context, std::string& args) {
    endwin();
    exit(0);
}

void register_builtins() {
    builtin_commands["cd"] = builtin_cd;
    builtin_commands["ls"] = builtin_ls;
    builtin_commands["exit"] = builtin_exit;
}