#include "m64p_binding_memory.h"
#include "../internal/core_interface.h"

// #########################################################
// ## RDRam Memory
// #########################################################

EXPORT const unsigned char* CALL rdramReadBuffer(u32 addr, u32 length) { return RdRamReadBuffer(addr, length); }
EXPORT u32 CALL rdramRead32(u32 addr) { return RdRamRead32(addr); }
EXPORT u16 CALL rdramRead16(u32 addr) { return RdRamRead16(addr); }
EXPORT u8 CALL rdramRead8(u32 addr) { return RdRamRead8(addr); }

// -------------------------------------------

EXPORT void CALL rdramWrite32(u32 addr, u32 value) { RdRamWrite32(addr, value); }
EXPORT void CALL rdramWrite16(u32 addr, u16 value) { RdRamWrite16(addr, value); }
EXPORT void CALL rdramWrite8(u32 addr, u8 value) { RdRamWrite8(addr, value); }

// #########################################################
// ## Rom Memory
// #########################################################

EXPORT const unsigned char* CALL romReadBuffer(u32 addr, u32 length) { return RomReadBuffer(addr, length); }
EXPORT u32 CALL romRead32(u32 addr) { return RomRead32(addr); }
EXPORT u16 CALL romRead16(u32 addr) { return RomRead16(addr); }
EXPORT u8 CALL romRead8(u32 addr) { return RomRead8(addr); }

// -------------------------------------------

EXPORT void CALL romWrite32(u32 addr, u32 value) { RomWrite32(addr, value); }
EXPORT void CALL romWrite16(u32 addr, u16 value) { RomWrite16(addr, value); }
EXPORT void CALL romWrite8(u32 addr, u8 value) { RomWrite8(addr, value); }

// #########################################################
// ## SaveStates
// #########################################################

EXPORT void CALL savestatesRefreshHack(void) { SaveStatesHackRefresh(); }