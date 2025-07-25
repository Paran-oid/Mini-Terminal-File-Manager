#include "builtins.hpp"

#include <ncurses.h>

#include <csignal>
#include <filesystem>

#include "context.hpp"

namespace fs = std::filesystem;

std::unordered_map<std::string, BuiltinFunc> builtin_commands;

void builtin_cd(TFM_Context& context, std::string& args) {
    if (args.empty()) {
        printw("No path entered\n");
    }
}
void builtin_ls(TFM_Context& context, std::string& args) {
    std::vector<std::string> files;
    std::string path = args;

    try {
        for (const auto& entry : fs::directory_iterator(path)) {
            if (fs::is_regular_file(entry.path())) {
                files.push_back(entry.path().filename().string());
            }
        }
    } catch (const fs::filesystem_error& e) {
        raise(SIGINT);
    }

    std::string x = "3";
}
void builtin_exit(TFM_Context& context, std::string& args) {
    endwin();
    std::exit(EXIT_SUCCESS);
}

void bultin_clear(TFM_Context& context, std::string& args) { clear(); }

void register_builtins() {
    builtin_commands["cd"] = builtin_cd;
    builtin_commands["ls"] = builtin_ls;
    builtin_commands["exit"] = builtin_exit;
    builtin_commands["clear"] = bultin_clear;
}