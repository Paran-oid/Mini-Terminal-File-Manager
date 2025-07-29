#ifndef INPUT_HPP
#define INPUT_HPP

#include <cstdint>

class TFMConfig;

class TFMInput {
   private:
    TFMConfig& m_conf;

   public:
    TFMInput(TFMConfig& conf) : m_conf{conf} {}

    void cursor_move();
	
    uint8_t process();
};

#endif