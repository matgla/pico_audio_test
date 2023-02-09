// #include <array>

// #include "ff.h"
// #include "diskio.h"

// #include <pico/sd_card.h>

// extern "C"
// {

// DSTATUS disk_status(BYTE pdrv)
// {
//     static_cast<void>(pdrv);
//     return 0;
// }

// DSTATUS disk_initialize(BYTE pdrv)
// {
//     static_cast<void>(pdrv);
//     sd_init_4pins();
//     sd_set_wide_bus(true);
//     return 0;
// }

// DRESULT disk_read (BYTE pdrv, BYTE* buff, LBA_t sector, UINT count)
// {
//     static_cast<void>(pdrv);
//     std::array<uint8_t, 255> buffer; 
//     for (std::size_t i = 0; i < count; )
//     sd_readblocks_sync(reinterpret_cast<uint32_t*>(buff), sector, count);
//     return RES_OK;
// }

// DRESULT disk_write (
//   BYTE pdrv,        /* [IN] Physical drive number */
//   const BYTE* buff, /* [IN] Pointer to the data to be written */
//   LBA_t sector,     /* [IN] Sector number to write from */
//   UINT count        /* [IN] Number of sectors to write */
// )
// {
//     sd_writeblocks_async(reinterpret_cast<const uint32_t*>(buff), sector, count);

//     int rc; 
//     while (!sd_write_complete(&rc))
//     {
//     };

//     return RES_OK;
// }

// DWORD get_fattime (void)
// {
//     return 0;
// }

// DRESULT disk_ioctl (
//   BYTE pdrv,     /* [IN] Drive number */
//   BYTE cmd,      /* [IN] Control command code */
//   void* buff     /* [I/O] Parameter and data buffer */
// )
// {
//     if (cmd == CTRL_SYNC)
//     {
//         return RES_OK;
//     }
//     return RES_OK;
// }

// }