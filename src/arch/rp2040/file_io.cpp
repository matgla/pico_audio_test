#include <unistd.h>

// This file contain IO stubs for RPI pico 
// Some of symbols must be wrapped by linker to override default 
// pico-SDK behaviour

extern "C"
{

extern ssize_t __real__write(int fd, const void *buf, size_t count);

ssize_t __wrap__write(int fd, const void *buf, size_t count)
{
   if (fd == STDIN_FILENO 
        || fd == STDOUT_FILENO 
        || fd == STDERR_FILENO)
    {
        return __real__write(fd, buf, count);
    }

    return 0;
}

extern ssize_t __real__read(int fd, void *buf, size_t count);

ssize_t __wrap__read(int fd, void *buf, size_t count)
{
    if (fd == STDIN_FILENO 
        || fd == STDOUT_FILENO 
        || fd == STDERR_FILENO)
    {
        return __real__read(fd, buf, count);
    }

    return 0;
}

} 

