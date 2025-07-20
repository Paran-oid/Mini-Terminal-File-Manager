#ifndef BUILTINS_HPP
#define BUILTINS_HPP

#include <functional>
#include <map>
#include <string>

class TFM_Context;

using BuiltinFunc = std::function<void(TFM_Context&, std::string&)>;
extern std::unordered_map<std::string, BuiltinFunc> builtin_commands;

void register_builtins();

#endif