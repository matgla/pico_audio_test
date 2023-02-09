#include "ui/app.hpp"

#include <cstdio>
#include <string_view>

#include <unistd.h>

#include "sine_command.hpp"
#include "argument_helpers.hpp"

namespace pico_audio
{
    
App::App()
    : commands_{
        Command{
            "help", 
            "shows manual", 
            "?cmd", 
            [this](std::string_view args){static_cast<void>(args); this->show_help();}, 
            [this](){this->show_help();}
        },
        Command{
            "sine", 
            "generate sine wave", 
            "freq", 
            &SineCommand::command, 
            &SineCommand::help
        }
    }
{
    puts("\n");
    puts("/----------------------------\\");
    puts("| Raspberry PICO - AUDIO DAC |");
    puts("\\----------------------------/");
}

bool App::read_char()
{
    char c;
    read(STDIN_FILENO, &c, 1);
    if (c == '\n' || c == 13)
    {
        command_[buffer_position_] = 0;
        return false;
    }
    if (c == '\b') // backspace 
    {
        if (buffer_position_ == 0)
        {
            return true;
        }
        --buffer_position_;
        command_[buffer_position_] = 0;
        write(STDOUT_FILENO, &c, 1);
        return true;
    }
    command_[buffer_position_] = c;
    write(STDOUT_FILENO, &c, 1);
    ++buffer_position_;
    return true;
}

void App::read_command()
{
    while (read_char())
    {
    }
}


std::string_view App::get_next_part()
{
    if (buffer_position_ == 0 || command_position_ == std::string_view::npos)
    {
        return "";
    }
    
    const Part part = pico_audio::get_next_part(
        std::string_view(command_.data() + command_position_));
    const std::string_view command = part.data;
    // trim leading whitespaces 

    if (command.size() + command_position_ == buffer_position_)
    {
        command_position_ = std::string_view::npos; 
    }
    else 
    {
        command_position_ = command_position_ + part.offset + command.size();
    }

    return command;
}

void App::process_command()
{
    const std::string_view command_name = get_next_part();
    const std::string_view whole_command(command_.data());

    const std::string_view all_arguments(command_.data() + command_position_, whole_command.size() - command_position_);
    const std::size_t args_index = all_arguments.find_first_not_of(whitespaces_string);

    for (const auto& cmd : commands_)
    {
        if (cmd.command.compare(command_name) == 0)
        {
            if (cmd.callback)
            {
                cmd.callback(all_arguments.substr(args_index, all_arguments.size() - args_index));
            }
        }
    }
}

void App::run()
{
    while (true)
    {
        printf("\n > ");
        buffer_position_ = 0;
        read_command();
        puts("");
        command_position_ = 0;
        process_command();
    } 
}

void App::show_help() 
{
    const std::string_view arg = get_next_part();
    if (arg.size() == 0)
    {
        puts("");
        puts("==================================");
        puts("= Raspberry Pico Audio Generator =");
        puts("==================================");
        puts("For more informations use: `help [command]`");
        puts("Available commands:");
        for (const auto& cmd : commands_)
        {
            printf("  %s - %s\n", cmd.command.data(), cmd.description.data());
        }
    }
    else 
    {
        puts("");
        for (const auto& cmd : commands_)
        {
            if (cmd.command == arg)
            {
                if (cmd.help)
                {
                    cmd.help();
                    return;
                }
                else 
                {
                    printf("Command %.*s has no help\n", arg.size(), arg.data());
                }
            }
        }

        printf("Can't find command: %.*s\n", arg.size(), arg.data());
    }   
}

} // namespace pico_audio
