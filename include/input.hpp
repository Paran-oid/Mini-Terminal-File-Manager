#ifndef INPUT_HPP
#define INPUT_HPP

#include <cstdint>

class TFMConfig;

class TFMInput {
   private:
    TFMConfig& m_conf;

   public:
    TFMInput(TFMConfig& conf) : m_conf{conf} {}

    uint8_t cursor_move(int32_t direction);
    uint8_t process();
};

#endif