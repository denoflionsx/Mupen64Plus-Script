#if !defined(__M64P_BINDING_MEMORY_H__)
#define __M64P_BINDING_MEMORY_H__

#include "m64p_types.h"
#include "m64p_memaccess.h"

EXPORT uint64 CALL MemRead64(uint32 addr);
EXPORT uint64 CALL MemReadU64(uint32 addr);
EXPORT void CALL MemWrite64(uint32 addr, uint64 value);
EXPORT void CALL MemWriteU64(uint32 addr, uint64 value);
EXPORT uint32 CALL MemRead32(uint32 addr);
EXPORT uint32 CALL MemReadU32(uint32 addr);
EXPORT void CALL MemWrite32(uint32 addr, uint32 value);
EXPORT void CALL MemWriteU32(uint32 addr, uint32 value);
EXPORT uint16 CALL MemRead16(uint32 addr);
EXPORT void CALL MemWrite16(uint32 addr, uint16 value);
EXPORT uint8 CALL MemRead8(uint32 addr);
EXPORT void CALL MemWrite8(uint32 addr, uint8 value);

#endif