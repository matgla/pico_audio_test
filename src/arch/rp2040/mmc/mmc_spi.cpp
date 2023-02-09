#include "arch/rp2040/mmc/mmc_spi.hpp"

#include <unistd.h>

namespace arch::rp2040::mmc
{

void SPIMMC::init()
{
    sleep(0.1f);
    write_command()
}

} // namespace arch::rp2040::mmc
