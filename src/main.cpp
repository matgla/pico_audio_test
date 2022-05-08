#include <array>
#include <cstdio>

#include <unistd.h>

#include <pico/stdlib.h> 

char cmd[255];
int buffer_position;

bool read_char()
{
    char c;
    read(STDIN_FILENO, &c, 1);
    if (c == '\n' || c == 13)
    {
        cmd[buffer_position] = 0;
        return false;
    }
    if (c == 9) // backspace 
    {
        if (buffer_position == 0)
        {
            return true;
        }
        --buffer_position;
        cmd[buffer_position] = 0;
        return true;
    }
    cmd[buffer_position] = c;
    write(STDOUT_FILENO, &c, 1);
    ++buffer_position;
    return true;
}

int main() 
{
    stdio_init_all();
    
    puts("/----------------------------\\");
    puts("| Raspberry PICO - AUDIO DAC |");
    puts("\\----------------------------/");

    // flush
    while (uart_is_readable(uart0))
    {
        uart_getc(uart0);
    }

    while (true)
    {
        printf("Write command: ");
        buffer_position = 0;
        while (read_char()) 
        {
        }

        printf("\n");
        printf("%s\n", cmd);
    }
}