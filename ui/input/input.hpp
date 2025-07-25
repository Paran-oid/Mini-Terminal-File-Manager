#ifndef INPUT_H
#define INPUT_H

#include <cstdint>
#include <string>
#include <vector>

class TFM_Context;

uint8_t TFM_handle_input_buf(TFM_Context& context,
                             std::vector<std::string>& output,
                             std::string& buf);
uint8_t TFM_input_process(TFM_Context& context);

#endif