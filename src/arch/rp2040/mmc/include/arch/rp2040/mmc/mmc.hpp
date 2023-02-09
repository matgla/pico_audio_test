#pragma once 

namespace arch::rp2040::mmc
{

class MMC
{
public:
    virtual ~MMC() = default; 

    virtual void init() = 0;
    virtual void write() = 0;
    virtual void read() = 0;
}

} // namespace arch::rp2040::mmc
