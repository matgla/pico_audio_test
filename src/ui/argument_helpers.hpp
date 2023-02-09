#pragma once 

#include <string_view>

namespace pico_audio
{
    
constexpr std::string_view whitespaces_string = " \n\r\t\f\v";

struct Part 
{
    std::size_t offset; 
    std::string_view data;
};

Part get_next_part(std::string_view data);

} // namespace pico_audio
