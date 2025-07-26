#include "builtins.hpp"

#include <ncurses.h>

#include <csignal>
#include <filesystem>
#include <misc.hpp>

#include "context.hpp"
#include "render.hpp"

namespace fs = std::filesystem;

std::unordered_map<std::string, BuiltinFunc> builtin_TFM_Commands;

void builtin_cd(TFM_Context& context, TFM_Command& cmd) {
    if (cmd.args.empty()) {
        printw("No path entered\n");
    }
}
void builtin_ls(TFM_Context& context, TFM_Command& cmd) {
    // TODO: make sure user doesn't enter more than one argument

    std::vector<std::string> files;
    std::string path;

    if (cmd.args.empty())
        path = "./";
    else
        path = cmd.args[0];

    try {
        for (const auto& entry : fs::directory_iterator(path)) {
            files.push_back(entry.path().filename().string());
        }
    } catch (const fs::filesystem_error& e) {
        raise(SIGINT);
    }

    if (TFM_ls_display(context, files) != EXIT_SUCCESS) {
        die("ls display failed");
    }
}

void builtin_exit(TFM_Context& context, TFM_Command& cmd) {
    endwin();
    std::exit(EXIT_SUCCESS);
}

void bultin_clear(TFM_Context& context, TFM_Command& cmd) { clear(); }

void register_builtins() {
    builtin_TFM_Commands["cd"] = builtin_cd;
    builtin_TFM_Commands["ls"] = builtin_ls;
    builtin_TFM_Commands["exit"] = builtin_exit;
    builtin_TFM_Commands["clear"] = bultin_clear;
}