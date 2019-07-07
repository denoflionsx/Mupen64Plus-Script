#include "m64p_binding_rdmem.h"
#include "../internal/core_interface.h"

// #########################################################
// ## RD Memory
// #########################################################

EXPORT uint64 CALL RdMemRead64(uint32 addr) { return RdRamRead64(addr); }
EXPORT uint64 CALL RdMemReadU64(uint32 addr) { return RdRamReadU64(addr); }
EXPORT void CALL RdMemWrite64(uint32 addr, uint64 value) { RdRamWrite64(addr, value); }
EXPORT void CALL RdMemWriteU64(uint32 addr, uint64 value) { RdRamWriteU64(addr, value); }
EXPORT uint32 CALL RdMemRead32(uint32 addr) { return RdRamRead32(addr); }
EXPORT uint32 CALL RdMemReadU32(uint32 addr) { return RdRamReadU32(addr); }
EXPORT void CALL RdMemWrite32(uint32 addr, uint32 value) { RdRamWrite32(addr, value); }
EXPORT void CALL RdMemWriteU32(uint32 addr, uint32 value) { RdRamWriteU32(addr, value); }
EXPORT uint16 CALL RdMemRead16(uint32 addr) { return RdRamRead16(addr); }
EXPORT void CALL RdMemWrite16(uint32 addr, uint16 value) { RdRamWrite16(addr, value); }
EXPORT uint8 CALL RdMemRead8(uint32 addr) { return RdRamRead8(addr); }
EXPORT void CALL RdMemWrite8(uint32 addr, uint8 value) { RdRamWrite8(addr, value); }