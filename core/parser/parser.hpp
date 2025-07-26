#ifndef PARSER_HPP
#define PARSE_HPP

#include <string>
#include <vector>

struct TFM_Command;

TFM_Command parser_command(const std::string& input);

#endif
