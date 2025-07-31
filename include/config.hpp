#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <filesystem>
#include <string>
#include <vector>

class TFMConfig {
   private:
    uint8_t m_started = 0;

   public:
    TFMConfig() = default;
    ~TFMConfig() = default;

    uint8_t get_started() const { return m_started; }
    void set_started(uint8_t started) { m_started = started; }
};

#endif