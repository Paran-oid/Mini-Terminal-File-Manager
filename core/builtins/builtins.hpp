#ifndef BUILTINS_HPP
#define BUILTINS_HPP

#include <functional>
#include <map>
#include <string>

struct TFM_Command;
class TFM_Context;

using BuiltinFunc = std::function<void(TFM_Context&, TFM_Command&)>;
extern std::unordered_map<std::string, BuiltinFunc> builtin_TFM_Commands;

void register_builtins();

#endif