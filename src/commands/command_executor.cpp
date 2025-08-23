#include "command_executor.hpp"

#include <algorithm>
#include <cctype>
#include <chrono>
#include <cmath>
#include <fstream>
#include <sstream>

#include "command_parser.hpp"
#include "config.hpp"
#include "cursor.hpp"
#include "dialog.hpp"
#include "path.hpp"
#include "rows.hpp"
#include "screen.hpp"
#include "utils.hpp"

#define LS_PADDING 2

void TFMCommandExecutor::clear_func(const TFMCommand& cmd) {
    (void)cmd;
    m_rows.clear();
    m_cursor.set(0, 0);
    m_screen.set_row_off(0);
}

void TFMCommandExecutor::cd_func(const TFMCommand& cmd) {
    if (cmd.positional.empty()) {
        return;
    }

    std::string path_str = cmd.positional[0];
    m_path.expand(path_str);

    if (path_str == "-") {
        auto temp = m_path.get_path();
        path_str = m_path.get_previous_path().string();
        m_path.set_previous_path(temp);
    }

    fs::path target_path(path_str);

    if (!fs::exists(target_path)) {
        manage_error(cmd, UNAVAILABLE_DIRECTORY);
        return;
    }

    try {
        // handles symlinks and relative paths
        target_path = fs::canonical(target_path);
    } catch (const fs::filesystem_error& e) {
        manage_error(cmd, UNAVAILABLE_DIRECTORY);
        return;
    }

    m_path.set_previous_path(m_path.get_path());
    m_path.set_path(target_path);
}

void TFMCommandExecutor::ls_func(const TFMCommand& cmd) {
    // handle flags
    bool show_hidden_files =
        std::any_of(cmd.flags.begin(), cmd.flags.end(),
                    [](const std::string& flag) { return flag == "a"; });

    // initialize the map
    bool single_path = false;
    std::unordered_map<fs::path, std::vector<fs::path>> path_file_map;

    if (cmd.positional.empty()) {
        path_file_map[m_path.get_path()];
        single_path = true;
    } else {
        if (cmd.positional.size() == 1) {
            const fs::path main_path = cmd.positional[0];
            if (!fs::exists(main_path)) {
                manage_error(cmd, UNAVAILABLE_DIRECTORY, {main_path});
                return;
            }
            path_file_map[main_path] = {};
            single_path = true;
        } else {
            for (const std::string& arg : cmd.positional) {
                if (!fs::exists(fs::path(arg))) {
                    manage_error(cmd, UNAVAILABLE_DIRECTORY, {fs::path(arg)});
                } else {
                    path_file_map[fs::path(arg)] = {};
                }
            }
        }
    }

    // get all current files/folders
    for (auto& path_file : path_file_map) {
        const fs::path& path = path_file.first;
        if (fs::is_regular_file(path)) {
            path_file.second.push_back(path_file.first);
            continue;
        }

        for (const auto& entry : fs::directory_iterator(path)) {
            std::string filename = entry.path().filename();
            if (!show_hidden_files && filename[0] == '.') {
                continue;
            }
            path_file.second.push_back(filename);
        }
    }

    // order the vectors of each path
    for (auto& path_file : path_file_map) {
        std::sort(
            path_file.second.begin(), path_file.second.end(),
            [](const std::string& a, const std::string& b) { return a < b; });
    }

    for (auto it = path_file_map.begin(); it != path_file_map.end(); it++) {
        // get longest length (we will get pair iterator returned)

        auto& path = it->first;
        auto& filenames = it->second;
        bool is_last_iterator = (std::next(it) == path_file_map.end());

        auto it_max_length = std::max_element(
            filenames.begin(), filenames.end(),
            [](const auto& a, const auto& b) {
                return a.string().length() < b.string().length();
            });

        if (it_max_length == filenames.end()) {
            return;
        }

        size_t max_length = it_max_length->string().length() + LS_PADDING;
        size_t cols = static_cast<size_t>(m_screen.get_cols() / max_length);
        size_t rows = static_cast<size_t>(std::ceil(
            static_cast<float>(filenames.size()) / static_cast<float>(cols)));
        bool is_file = fs::is_regular_file(path);
        std::ostringstream row_builder;

        if (!single_path && !is_file) {
            m_rows.append(path.string() + ":");
        } else {
            if (!single_path) {
                m_rows.append(path.string());
            }
            if (is_file) {
                continue;
            }
        }

        for (size_t i = 0; i < rows; i++) {
            for (size_t j = 0; j < cols; j++) {
                size_t calculated_index = j * rows + i;
                if (calculated_index >= filenames.size()) {
                    continue;
                }

                std::string filename =
                    ls_format(filenames[calculated_index], max_length);
                row_builder << filename;
            }
            m_rows.append(row_builder.str());

            row_builder.str("");
            row_builder.clear();
        }

        if (!is_last_iterator) {
            m_rows.append("");
        }
    }
}

void TFMCommandExecutor::pwd_func(const TFMCommand& cmd) {
    (void)cmd;
    m_rows.append(m_path.get_path().string());
}

void TFMCommandExecutor::whoami_func(const TFMCommand& cmd) {
    (void)cmd;
    m_rows.append(m_config.get_username());
}

void TFMCommandExecutor::cat_func(const TFMCommand& cmd) { (void)cmd; }

void TFMCommandExecutor::cp_func(const TFMCommand& cmd) {
    if (cmd.positional.empty() || cmd.positional.size() == 1) {
        manage_error(cmd, MISSING_FILE_OPERAND);
        return;
    }

    bool is_interactive = false;
    __attribute__((unused)) bool is_forced = false;
    __attribute__((unused)) bool is_src_newer_than_dest = false;
    bool is_verbose = false;
    bool is_recursive = false;

    for (const std::string& flag : cmd.flags) {
        if (flag == "i") {
            is_interactive = true;
        } else if (flag == "f") {
            is_forced = true;
        } else if (flag == "u") {
            is_src_newer_than_dest = true;
        } else if (flag == "r") {
            is_recursive = true;
        } else if (flag == "v") {
            is_verbose = true;
        }
    }

    std::vector<std::string> src_paths;

    for (size_t i = 0; i < cmd.positional.size() - 1; i++) {
        const std::string& arg = cmd.positional[i];
        if (!fs::exists(arg)) {
            manage_error(cmd, MISSING_FILE_SOURCE, {arg});
        } else {
            src_paths.push_back(fs::absolute(arg).string());
        }
    }

    std::string dst = fs::absolute(cmd.positional.back()).string();
    std::ostringstream os;
    for (const auto& src_path : src_paths) {
        fs::path src(src_path);
        fs::path target(dst);

        if (src == target) {
            manage_error(cmd, TFMCommandErrorCode::SAME_FILE_PASSED,
                         {src.filename()});
            continue;
        }

        if (fs::is_directory(src_path)) {
            if (!is_recursive) {
                manage_error(cmd, FLAG_NOT_SPECIFIED, {"r", target.filename()});
                continue;
            }

            target /= src.filename();

            if (fs::exists(target) && is_interactive) {
                std::string prompt = m_dialog.receive(
                    "cp: overwrite " + target.filename().string() + "?");

                if (std::toupper(prompt[0]) != 'Y') {
                    continue;
                }
            }

            try {
                fs::create_directories(target);
            } catch (fs::filesystem_error& e) {
                manage_error(cmd, FAILED_DIRECTORY_CREATION, {target});
                continue;
            }

            for (const auto& entry : fs::recursive_directory_iterator(src)) {
                const auto& path = entry.path();
                fs::path relative = fs::relative(path, src);
                const auto& new_path = target / relative;

                try {
                    fs::copy(path, new_path,
                             fs::copy_options::overwrite_existing |
                                 (is_recursive ? fs::copy_options::recursive
                                               : fs::copy_options::none));
                } catch (fs::filesystem_error& e) {
                    manage_error(cmd, FILESYSTEM_ERROR, {e.what()});
                    continue;
                }

                if (is_verbose) {
                    os << "copied: " << path.filename() << " -> "
                       << new_path.filename();
                    m_rows.append(os.str());
                    os.str("");
                }
            }
        } else {
            fs::path resulting_dst;
            if (fs::is_directory(target)) {
                resulting_dst = target / src.filename();
            } else {
                resulting_dst = target;
                if (!fs::exists(resulting_dst) &&
                    resulting_dst.extension().empty()) {
                    manage_error(cmd, TARGET_DIRECTORY_NON_EXISTANT,
                                 {resulting_dst.filename()});
                    break;
                }
            }

            if (fs::exists(resulting_dst) && is_interactive) {
                std::string prompt =
                    m_dialog.receive("cp: overwrite " +
                                     resulting_dst.filename().string() + "? ");
                if (std::toupper(prompt[0]) != 'Y') {
                    continue;
                }
            }

            try {
                fs::copy_file(src, resulting_dst,
                              fs::copy_options::overwrite_existing);
            } catch (fs::filesystem_error& e) {
                manage_error(cmd, FILESYSTEM_ERROR, {e.what()});
                continue;
            }

            if (is_verbose) {
                os << "copied " << src.filename() << " -> "
                   << resulting_dst.filename();
                m_rows.append(os.str());
                os.str("");
            }
        }
    }
}

void TFMCommandExecutor::mv_func(const TFMCommand& cmd) {
    // syntax
    // mv [options] src dst
    // rename file: mv file1.txt file2.txt
    // move file: file.txt path/to/dst/
    // mv file1.txt file2.txt file3.txt /backup/
    // rename and move: mv file.txt /path/to/destination/newname.txt
    // mv myfolder/ /new/location/
    // mv oldfolder newfolder

    /*
    Info about flags:
    Useful Options
        Option	Meaning
        -i	Interactive: asks before overwriting existing files
        -n	No-clobber: don’t overwrite existing files
        -v	Verbose: shows what is happening
    */

    if (cmd.positional.size() < 2) {
        manage_error(cmd, MISSING_FILE_OPERAND);
        return;
    }

    bool is_interactive = false;
    bool is_verbose = false;
    bool is_no_clobber = false;

    for (const auto& flag : cmd.flags) {
        if (flag == "i") {
            is_interactive = true;
        } else if (flag == "v") {
            is_verbose = true;
        } else if (flag == "n") {
            is_no_clobber = true;
        }
    }

    fs::path dst_path = cmd.positional.back();
    std::vector<fs::path> src_paths;

    bool dst_is_directory = fs::exists(dst_path) && fs::is_directory(dst_path);

    for (uint32_t i = 0; i < cmd.positional.size() - 1; i++) {
        const fs::path arg = cmd.positional[i];
        if (!fs::exists(arg)) {
            manage_error(cmd, MISSING_FILE_DESTINATION, {arg.filename()});
            return;
        }
        src_paths.push_back(arg);
    }

    std::ostringstream os;
    if (dst_is_directory) {
        for (const auto& src_path : src_paths) {
            const fs::path new_path = dst_path / src_path.filename();

            if (fs::exists(new_path) && is_no_clobber) {
                continue;
            }

            if (fs::exists(dst_path) && is_interactive) {
                std::string resp = m_dialog.receive(
                    "mv: overwrite '" + new_path.filename().string() + "'? ");

                if (str_to_upper(resp) != "Y") {
                    continue;
                }
            }

            try {
                fs::rename(src_path, new_path);
            } catch (fs::filesystem_error& e) {
                manage_error(cmd, FILESYSTEM_ERROR, {e.what()});
                continue;
            }

            if (is_verbose) {
                os << "renamed " << src_path.filename().string() << " -> "
                   << new_path.string();
                m_rows.append(os.str());
                os.str("");
            }
        }
    } else {
        if (src_paths.size() > 1) {
            manage_error(cmd, DESTINATION_NOT_A_DIRECTORY,
                         {dst_path.filename()});
            return;
        }

        if (fs::is_directory(src_paths[0]) &&
            fs::is_regular_file(dst_path.filename())) {
            manage_error(cmd, OVERWRITE_NON_DIR_WITH_DIR,
                         {src_paths[0], dst_path});
            return;
        }

        if (fs::exists(dst_path) && is_no_clobber) {
            return;
        }

        if (fs::exists(dst_path) && is_interactive) {
            std::string resp = m_dialog.receive(
                "mv: overwrite '" + dst_path.filename().string() + "'? ");

            if (str_to_upper(resp) != "Y") {
                return;
            }
        }

        try {
            fs::rename(src_paths[0], dst_path);
        } catch (fs::filesystem_error& e) {
            manage_error(cmd, FILESYSTEM_ERROR, {e.what()});
            return;
        }

        if (is_verbose) {
            os << "renamed " << src_paths[0].filename() << " -> "
               << dst_path.filename();
            m_rows.append(os.str());
        }
    }
}

void TFMCommandExecutor::rm_func(const TFMCommand& cmd) {
    // rm [options] object

    /*
        -f	Force: ignore nonexistent files, never prompt.
        -i	Interactive: ask before deleting each file.
        -I	Prompt once before removing more than three files or
       recursively.

        -r or -R	Recursive: remove directories and their
       contents. -v	Verbose: show what is being deleted.
    */

    bool is_interactive = false;
    bool is_verbose = false;
    bool is_recursive = false;
    bool is_forced = false;

    for (const auto& flag : cmd.flags) {
        if (flag == "i") {
            is_interactive = true;
        } else if (flag == "v") {
            is_verbose = true;
        } else if (flag == "r") {
            is_recursive = true;
        } else if (flag == "f") {
            is_forced = true;
        }
    }

    if (is_forced) {
        is_interactive = false;
    }

    if (cmd.positional.empty()) {
        manage_error(cmd, MISSING_FILE_OPERAND);
        return;
    }

    std::ostringstream os;
    for (const auto& path_str : cmd.positional) {
        fs::path path(path_str);
        if (!fs::exists(path) && !is_forced) {
            manage_error(cmd, UNAVAILABLE_DIRECTORY, {path.filename()});
            continue;
        }

        if (fs::is_directory(path) && !is_recursive) {
            manage_error(cmd, EXPECTED_RECURSIVE_FLAG, {path.filename()});
            continue;
        }

        if (fs::is_regular_file(path)) {
            if (is_interactive) {
                std::string prompt = m_dialog.receive(
                    "are you sure you want to delete the file: " +
                    path.filename().string() + "? ");
                if (std::toupper(prompt[0]) != 'Y') {
                    continue;
                }
            }

            try {
                fs::remove(path);

            } catch (fs::filesystem_error& e) {
                manage_error(cmd, FILESYSTEM_ERROR, {e.what()});
                continue;
            }

        } else {
            if (is_interactive) {
                std::string prompt = m_dialog.receive(
                    "are you sure you want to delete the directory: " +
                    path.filename().string() + "? ");

                if (std::toupper(prompt[0]) != 'Y') {
                    continue;
                }
            }
            try {
                fs::remove_all(path);

            } catch (fs::filesystem_error& e) {
                manage_error(cmd, FILESYSTEM_ERROR, {e.what()});
                continue;
            }
        }

        if (is_verbose) {
            os << "removed " << path;
            m_rows.append(os.str());
            os.str("");
        }
    }
}

void TFMCommandExecutor::mkdir_func(const TFMCommand& cmd) {
    if (cmd.positional.empty()) {
        manage_error(cmd, MISSING_OPERAND);
        return;
    }

    for (const auto& arg : cmd.positional) {
        fs::path path = m_path.get_path() / arg;
        try {
            fs::create_directories(path);
        } catch (const fs::filesystem_error& e) {
            manage_error(cmd, FAILED_DIRECTORY_CREATION, {arg});
        }
    }
}

void TFMCommandExecutor::touch_func(const TFMCommand& cmd) {
    // TODO: implement most important flags

    if (cmd.positional.empty()) {
        manage_error(cmd, MISSING_FILE_OPERAND);
        return;
    }

    for (const std::string& arg : cmd.positional) {
        // ignore flags
        if (arg[0] == '-') {
            continue;
        }

        fs::path path = fs::path(arg);

        if (fs::exists(path)) {
            auto now = std::chrono::file_clock::now();
            try {
                fs::last_write_time(path, now);

            } catch (fs::filesystem_error& e) {
                manage_error(cmd, FILESYSTEM_ERROR, {e.what()});
            }
        } else {
            try {
                std::ofstream ofs(path);
                ofs.close();
            } catch (const std::ios_base::failure& e) {
                manage_error(cmd, FILESYSTEM_ERROR, {e.what()});
            }
        }
    }
}

void TFMCommandExecutor::manage_error(const TFMCommand& cmd,
                                      TFMCommandErrorCode code,
                                      const std::vector<std::string> data) {
    // TODO: maybe get rid of repetition
    std::ostringstream message_buf;
    switch (code) {
        case INVALID_COMMAND:
            message_buf << cmd.name << ": command not found";
            break;
        case UNAVAILABE_DIRECTORY_OR_FILE:
            if (data.empty()) {
                throw std::runtime_error(
                    "TFMCommandExecutor::manage_error: expected data to be "
                    "passed");
            }
            message_buf << cmd.name << ": " << data[0]
                        << ": no such file or directory";
            break;
        case UNAVAILABLE_DIRECTORY:
            if (data.empty()) {
                throw std::runtime_error(
                    "TFMCommandExecutor::manage_error: expected data to be "
                    "passed");
            }
            message_buf << cmd.name << ": " << data[0]
                        << ": no such file or directory";
            break;
        case MISSING_OPERAND:
            message_buf << cmd.name << ": " << "missing operand";
            break;
        case MISSING_FILE_OPERAND:
            if (cmd.positional.empty()) {
                message_buf << cmd.name << ": " << "missing file operand";
            } else {
                if (data.empty()) {
                    throw std::runtime_error(
                        "TFMCommandExecutor::manage_error: expected data to be "
                        "passed");
                }
                message_buf << cmd.name << ": "
                            << "missing file operand after: '" << data[0]
                            << "'";
            }
            break;
        case MISSING_FILE_DESTINATION:
            if (data.empty()) {
                throw std::runtime_error(
                    "TFMCommandExecutor::manage_error: expected data to be "
                    "passed");
            }
            message_buf << cmd.name << ": "
                        << "missing destination file operand after '" << data[0]
                        << "'";
            break;
        case MISSING_FILE_SOURCE:
            if (data.empty()) {
                throw std::runtime_error(
                    "TFMCommandExecutor::manage_error: expected data to be "
                    "passed");
            }
            message_buf << cmd.name << ": "
                        << "missing source file operand after '" << data[0]
                        << "'";
            break;
        case FAILED_DIRECTORY_CREATION:
            if (data.empty()) {
                message_buf << cmd.name << ": " << "failed creating directory'";
            } else {
                message_buf << cmd.name << ": " << "failed creating directory '"
                            << data[0];
            }
            break;
        case FLAG_NOT_SPECIFIED:
            if (data.empty() || data.size() < 2) {
                throw std::runtime_error(
                    "TFMCommandExecutor::manage_error: expected data to be "
                    "passed");
            }
            message_buf << cmd.name << ": -" << data[0]
                        << " not specified; omitting directory: " << data[1];
            break;
        case SAME_FILE_PASSED:
            if (data.empty()) {
                throw std::runtime_error(
                    "TFMCommandExecutor::manage_error: expected data to be "
                    "passed");
            }
            message_buf << cmd.name << ": '" << data[0] << "' and '" << data[0]
                        << "' are the same file";
            break;
        case TARGET_DIRECTORY_NON_EXISTANT:
            if (data.empty()) {
                throw std::runtime_error(
                    "TFMCommandExecutor::manage_error: expected data to be "
                    "passed");
            }
            message_buf << cmd.name << ": " << "missing directory: '"
                        << data[0];
            break;
        case DESTINATION_NOT_A_DIRECTORY:
            if (data.empty()) {
                throw std::runtime_error(
                    "TFMCommandExecutor::manage_error: expected data to be "
                    "passed");
            }
            message_buf << cmd.name << ": target: '" << data[0]
                        << ": Not a directory";
            break;
        case OVERWRITE_NON_DIR_WITH_DIR:
            if (data.size() < 2) {
                throw std::runtime_error(
                    "TFMCommandExecutor::manage_error: expected 2 parameters "
                    "to be "
                    "passed");
            }
            message_buf << cmd.name << ": cannot overwrite non-directory '"
                        << data[0] << "' with directory '" << data[1] << "\'";
            break;
        case EXPECTED_RECURSIVE_FLAG:
            if (data.empty()) {
                throw std::runtime_error(
                    "TFMCommandExecutor::manage_error: expected data to be "
                    "passed");
            }
            message_buf << cmd.name << ": cannot remove '" << data[0]
                        << "/': is a directory";
            break;

        case FILESYSTEM_ERROR:
            if (data.empty()) {
                throw std::runtime_error(
                    "TFMCommandExecutor::manage_error: expected data to be "
                    "passed");
            }
            message_buf << cmd.name << ": " << data[0];
            break;
        default:
            break;
    }

    m_rows.append(message_buf.str());
}