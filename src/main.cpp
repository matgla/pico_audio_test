#include <pico/stdlib.h> 


#include "ui/app.hpp"
#include "dac/dac.hpp"

#include <array>
#include <bitset>
#include <cstdio>

#include <unistd.h>
#include <fcntl.h>

#include "ff.h"

#include <eul/container/static_vector.hpp>

void flush_stdio()
{
    while (uart_is_readable(uart0))
    {
        uart_getc(uart0);
    }
}

int main() 
{
    set_sys_clock_khz(176000, true);
    stdio_init_all();

    // // pico_audio::DAC dac;

    // puts("DAC initialized");
    // pico_audio::App app;
    // flush_stdio();


    FILE* f = fopen("test.txt", "r");
    if (f == nullptr)
    {
        printf("Can't open test.txt\n");
    }
    else 
    {
        int ch = 0;
        while (ch != EOF)
        {
            ch = fgetc(f);
            if (ch == EOF)
            {
                printf("EE\n");
                break;
            }
            printf("%c", ch);
        }
    }

    fclose(f);

    // app.run();

    while (true)
    {
        // while (read_char()) 
        // {
        // }

        // printf("\n");
        // printf("%s\n", cmd);
    }
}

