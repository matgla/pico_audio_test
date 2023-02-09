#include "sine_command.hpp"

#include <cstdio>

#include "argument_helpers.hpp"

namespace pico_audio
{
    
void SineCommand::help()
{
    puts("sine - generate sine wave");
    puts("command: sine frequency");
    puts("arguments: ");
    puts("  frequency: wave frequency in form value[k]");
    puts("Example: ");
    puts("  sine 1000 - generates sine wave with frequency 1000 hz");
    puts("  sine 10k - generates sine wave with frequency 10000 hz");
}

void SineCommand::command(std::string_view args)
{
    const Part arg = get_next_part(args);
    
    const std::size_t offset = arg.offset + arg.data.size();
    const std::string_view rest(args.data() + offset, args.size() - offset);

    if (rest.find_first_not_of(whitespaces_string) != std::string_view::npos)
    {
        printf("Can't parse arguments, check `help sine` for command format\n");
        printf("Passed arguments: %.*s\n", args.size(), args.data());
        return;
    }

    printf("Generate sine wave with frequency: %.*s\n", arg.data.size(), arg.data.data());

    
}

} // namespace pico_audio
