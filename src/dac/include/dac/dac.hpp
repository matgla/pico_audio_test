#pragma once 

#include <cstdint>

namespace pico_audio
{
    
class DAC 
{
public:
    DAC();

    static void samplerate(uint32_t rate);
private:
    static void samplerate_pwm(uint32_t rate, int pin_slice);
    static void init_pwm(int pin);
};

} // namespace pico_audio
