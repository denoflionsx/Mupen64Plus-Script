#include "m64p_binding_memory.h"
#include "../internal/core_interface.h"

// #########################################################
// ## RDRam Memory
// #########################################################

EXPORT uint64 CALL rdramRead64(uint32 addr) { return RdRamRead64(addr); }
EXPORT uint64 CALL rdramReadU64(uint32 addr) { return RdRamReadU64(addr); }
EXPORT void CALL rdramWrite64(uint32 addr, uint64 value) { RdRamWrite64(addr, value); }
EXPORT void CALL rdramWriteU64(uint32 addr, uint64 value) { RdRamWriteU64(addr, value); }
EXPORT uint32 CALL rdramRead32(uint32 addr) { return RdRamRead32(addr); }
EXPORT uint32 CALL rdramReadU32(uint32 addr) { return RdRamReadU32(addr); }
EXPORT void CALL rdramWrite32(uint32 addr, uint32 value) { RdRamWrite32(addr, value); }
EXPORT void CALL rdramWriteU32(uint32 addr, uint32 value) { RdRamWriteU32(addr, value); }
EXPORT uint16 CALL rdramRead16(uint32 addr) { return RdRamRead16(addr); }
EXPORT void CALL rdramWrite16(uint32 addr, uint16 value) { RdRamWrite16(addr, value); }
EXPORT uint8 CALL rdramRead8(uint32 addr) { return RdRamRead8(addr); }
EXPORT void CALL rdramWrite8(uint32 addr, uint8 value) { RdRamWrite8(addr, value); }

// #########################################################
// ## Rom Memory
// #########################################################

EXPORT uint64 CALL romRead64(uint32 addr) { return RomRead64(addr); }
EXPORT uint64 CALL romReadU64(uint32 addr) { return RomReadU64(addr); }
EXPORT void CALL romWrite64(uint32 addr, uint64 value) { RomWrite64(addr, value); }
EXPORT void CALL romWriteU64(uint32 addr, uint64 value) { RomWriteU64(addr, value); }
EXPORT uint32 CALL romRead32(uint32 addr) { return RomRead32(addr); }
EXPORT uint32 CALL romReadU32(uint32 addr) { return RomReadU32(addr); }
EXPORT void CALL romWrite32(uint32 addr, uint32 value) { RomWrite32(addr, value); }
EXPORT void CALL romWriteU32(uint32 addr, uint32 value) { RomWriteU32(addr, value); }
EXPORT uint16 CALL romRead16(uint32 addr) { return RomRead16(addr); }
EXPORT void CALL romWrite16(uint32 addr, uint16 value) { RomWrite16(addr, value); }
EXPORT uint8 CALL romRead8(uint32 addr) { return RomRead8(addr); }
EXPORT void CALL romWrite8(uint32 addr, uint8 value) { RomWrite8(addr, value); }