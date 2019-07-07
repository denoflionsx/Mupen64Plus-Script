#if !defined(__M64P_BINDING_RDMEM_H__)
#define __M64P_BINDING_RDMEM_H__

#include "m64p_types.h"
#include "m64p_rdmem.h"

EXPORT uint64 CALL RdMemRead64(uint32 addr);
EXPORT uint64 CALL RdMemReadU64(uint32 addr);
EXPORT void CALL RdMemWrite64(uint32 addr, uint64 value);
EXPORT void CALL RdMemWriteU64(uint32 addr, uint64 value);
EXPORT uint32 CALL RdMemRead32(uint32 addr);
EXPORT uint32 CALL RdMemReadU32(uint32 addr);
EXPORT void CALL RdMemWrite32(uint32 addr, uint32 value);
EXPORT void CALL RdMemWriteU32(uint32 addr, uint32 value);
EXPORT uint16 CALL RdMemRead16(uint32 addr);
EXPORT void CALL RdMemWrite16(uint32 addr, uint16 value);
EXPORT uint8 CALL RdMemRead8(uint32 addr);
EXPORT void CALL RdMemWrite8(uint32 addr, uint8 value);

#endif