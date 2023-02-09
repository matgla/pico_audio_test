#include "argument_helpers.hpp"

namespace pico_audio
{
    

Part get_next_part(std::string_view data)
{
    if (data.size() == 0) 
    {
        return {
            .offset = 0, 
            .data = ""
        };
    }

    // trim leading whitespaces 
    const std::size_t command_start = data.find_first_not_of(whitespaces_string); 
    const std::size_t command_end = data.find_first_of(whitespaces_string);
    
    const std::size_t size = (command_end == std::string_view::npos 
            ? data.size() : command_end) - command_start;

    return {
        .offset = command_start, 
        .data = data.substr(command_start, size)
    };
}

} // namespace pico_audio
