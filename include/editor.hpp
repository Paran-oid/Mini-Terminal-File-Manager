#pragma

#include "config.hpp"
#include "input.hpp"
#include "renderer.hpp"

class TFMEditor {
   private:
    TFMInput input;
    TFMRenderer renderer;
    TFMConfig config;

   public:
    TFMEditor() = default;
    ~TFMEditor() = default;
};