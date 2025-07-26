#ifndef RENDER_H
#define RENDER_H

#include <cstdint>

#include "context.hpp"

uint8_t TFM_ls_display(TFM_Context& context,
                       std::vector<std::string>& filenames);
uint8_t TFM_screen_refresh(TFM_Context& context);

#endif