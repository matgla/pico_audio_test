#pragma once 

#include <array>
#include <cstdint>
#include <string_view>

#include <eul/functional/function.hpp>

namespace pico_audio
{

constexpr std::size_t command_buffer_size = 128;

class App final
{
public: 
    App();

    void run();

private:
    bool read_char();
    void read_command();
    void process_command(); 
    std::string_view get_next_part();
    std::string_view trim_leading_whitespaces(std::string_view arg);

    void show_help();

    uint8_t buffer_position_;
    std::size_t command_position_;
    std::array<char, command_buffer_size> command_;

    struct Command
    {
        std::string_view command;
        std::string_view description;
        std::string_view arguments_format;
        eul::function<void(std::string_view args), sizeof(void*)> callback; 
        eul::function<void(), sizeof(void*)> help; 
    };

    std::array<Command, 2> commands_; // how to deduce size?
};

} // namespace pico_audio
