#include "parser.hpp"

#include <sstream>
#include <cstdint>

Command parser_command(const std::string& input) {
    Command c;
    std::istringstream iss(input);
	std::string token;
	uint8_t assigned_command = 0;

	while(iss >> token) {

	}

}