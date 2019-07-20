#if !defined(__M64P_BINDING_MEMORY_H__)
#define __M64P_BINDING_MEMORY_H__

#include "m64p_types.h"
#include "m64p_memaccess.h"

// #########################################################
// ## RDRam Memory
// #########################################################

EXPORT const unsigned char* CALL rdramReadBuffer(u32 addr, u32 length);
EXPORT u64 CALL rdramRead64(u32 addr);
EXPORT u32 CALL rdramRead32(u32 addr);
EXPORT u16 CALL rdramRead16(u32 addr);
EXPORT u8 CALL rdramRead8(u32 addr);

// -------------------------------------------

EXPORT void CALL rdramWrite64(u32 addr, u64 value);
EXPORT void CALL rdramWrite32(u32 addr, u32 value);
EXPORT void CALL rdramWrite16(u32 addr, u16 value);
EXPORT void CALL rdramWrite8(u32 addr, u8 value);

// #########################################################
// ## Rom Memory
// #########################################################

EXPORT const unsigned char* CALL romReadBuffer(u32 addr, u32 length);
EXPORT u64 CALL romRead64(u32 addr);
EXPORT u32 CALL romRead32(u32 addr);
EXPORT u16 CALL romRead16(u32 addr);
EXPORT u8 CALL romRead8(u32 addr);

// -------------------------------------------

EXPORT void CALL romWrite64(u32 addr, u64 value);
EXPORT void CALL romWrite32(u32 addr, u32 value);
EXPORT void CALL romWrite16(u32 addr, u16 value);
EXPORT void CALL romWrite8(u32 addr, u8 value);

EXPORT void CALL savestatesRefreshHack(void);

#endif