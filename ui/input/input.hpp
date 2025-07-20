#ifndef INPUT_H
#define INPUT_H

#include <context.hpp>
#include <cstdint>

uint8_t TFM_handle_input_buf(const std::string& buf);
uint8_t TFM_input_process(TFM_Context& context);

#endif