#pragma once 

#include "arch/rp2040/mmc/mmc.hpp"

#include <unistd.h>

namespace arch::rp2040::mmc
{
    
class SPIMMC : public MMC 
{
public:
    void init() override;
};

} // namespace arch::rp2040::mmc
