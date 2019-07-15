#if !defined(__M64P_BINDING_MEMORY_H__)
#define __M64P_BINDING_MEMORY_H__

#include "m64p_types.h"
#include "m64p_memaccess.h"

EXPORT const char* CALL rdramReadBuffer(uint32 addr, uint32 length);
EXPORT uint64 CALL rdramRead64(uint32 addr);
EXPORT uint64 CALL rdramReadU64(uint32 addr);
EXPORT void CALL rdramWrite64(uint32 addr, uint64 value);
EXPORT void CALL rdramWriteU64(uint32 addr, uint64 value);
EXPORT uint32 CALL rdramRead32(uint32 addr);
EXPORT uint32 CALL rdramReadU32(uint32 addr);
EXPORT void CALL rdramWrite32(uint32 addr, uint32 value);
EXPORT void CALL rdramWriteU32(uint32 addr, uint32 value);
EXPORT uint16 CALL rdramRead16(uint32 addr);
EXPORT void CALL rdramWrite16(uint32 addr, uint16 value);
EXPORT uint8 CALL rdramRead8(uint32 addr);
EXPORT void CALL rdramWrite8(uint32 addr, uint8 value);

EXPORT uint64 CALL romRead64(uint32 addr);
EXPORT uint64 CALL romReadU64(uint32 addr);
EXPORT void CALL romWrite64(uint32 addr, uint64 value);
EXPORT void CALL romWriteU64(uint32 addr, uint64 value);
EXPORT uint32 CALL romRead32(uint32 addr);
EXPORT uint32 CALL romReadU32(uint32 addr);
EXPORT void CALL romWrite32(uint32 addr, uint32 value);
EXPORT void CALL romWriteU32(uint32 addr, uint32 value);
EXPORT uint16 CALL romRead16(uint32 addr);
EXPORT void CALL romWrite16(uint32 addr, uint16 value);
EXPORT uint8 CALL romRead8(uint32 addr);
EXPORT void CALL romWrite8(uint32 addr, uint8 value);

EXPORT void CALL savestatesRefreshHack(void);

#endif