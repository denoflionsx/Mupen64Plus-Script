#include "m64p_binding_memory.h"
#include "../internal/core_interface.h"

// #########################################################
// ## RD Memory
// #########################################################

EXPORT uint64 CALL MemRead64(uint32 addr) { return RdRamRead64(addr); }
EXPORT uint64 CALL MemReadU64(uint32 addr) { return RdRamReadU64(addr); }
EXPORT void CALL MemWrite64(uint32 addr, uint64 value) { RdRamWrite64(addr, value); }
EXPORT void CALL MemWriteU64(uint32 addr, uint64 value) { RdRamWriteU64(addr, value); }
EXPORT uint32 CALL MemRead32(uint32 addr) { return RdRamRead32(addr); }
EXPORT uint32 CALL MemReadU32(uint32 addr) { return RdRamReadU32(addr); }
EXPORT void CALL MemWrite32(uint32 addr, uint32 value) { RdRamWrite32(addr, value); }
EXPORT void CALL MemWriteU32(uint32 addr, uint32 value) { RdRamWriteU32(addr, value); }
EXPORT uint16 CALL MemRead16(uint32 addr) { return RdRamRead16(addr); }
EXPORT void CALL MemWrite16(uint32 addr, uint16 value) { RdRamWrite16(addr, value); }
EXPORT uint8 CALL MemRead8(uint32 addr) { return RdRamRead8(addr); }
EXPORT void CALL MemWrite8(uint32 addr, uint8 value) { RdRamWrite8(addr, value); }