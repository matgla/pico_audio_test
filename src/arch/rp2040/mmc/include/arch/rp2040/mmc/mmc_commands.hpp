#pragma once 

#include <cstdint>

namespace arch::rp2040::mmc
{
    
// FRAME 
// 0b01xxxxxx -> x command value 1 byte
// 0xaaaaaaaa -> a argument 4 byte 
// 0bccccccc1 -> c crc checksum 1 byte 

enum class Command : uint32_t
{
    GO_IDLE_STATE = 0,
    SEND_IF_COND  = 0x000001aa,

};

} // namespace arch::rp2040::mmc
