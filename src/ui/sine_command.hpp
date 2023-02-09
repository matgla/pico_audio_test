#pragma once 

#include <string_view>

namespace pico_audio
{
    
class SineCommand
{
public:
    static void help();
    static void command(std::string_view args);
};

} // namespace pico_audio
