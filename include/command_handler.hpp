#ifndef COMMAND_HANDLER_HPP
#define COMMAND_HANDLER_HPP

#include <functional>
#include <string>
#include <unordered_map>
#include <vector>

class TFMPathHandler;
class TFMRows;
class TFMScreen;

using command_func = std::function<void(const std::vector<std::string>&)>;

enum TFMCommandErrorCode { INVALID, UNAVAILABLE_DIRECTORY };

class TFMCommandHandler {
   private:
    TFMPathHandler& m_path;
    TFMRows& m_rows;
    TFMScreen& m_screen;

    std::vector<std::string> m_args;
    std::unordered_map<std::string, command_func> match_table;
    void match_table_init();

    void clear_func(const std::vector<std::string>& args);
    void cd_func(const std::vector<std::string>& args);
    void ls_func(const std::vector<std::string>& args);
    void pwd_func(const std::vector<std::string>& args);
    void manage_error(const std::vector<std::string>& args,
                      TFMCommandErrorCode code);

    std::vector<std::string> parse(const std::string& command);

   public:
    TFMCommandHandler(TFMPathHandler& path, TFMRows& rows, TFMScreen& screen)
        : m_path{path}, m_rows{rows}, m_screen(screen) {
        match_table_init();
    }
    ~TFMCommandHandler() = default;

    void process(const std::string& command);
};

#endif