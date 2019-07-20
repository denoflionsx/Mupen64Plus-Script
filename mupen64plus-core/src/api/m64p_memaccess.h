/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
*   Mupen64plus-core - api/frontend.c                                     *
*   Mupen64Plus homepage: https://mupen64plus.org/                        *
*   Copyright (C) 2012 CasualJames                                        *
*   Copyright (C) 2009 Richard Goedeken                                   *
*                                                                         *
*   This program is free software; you can redistribute it and/or modify  *
*   it under the terms of the GNU General Public License as published by  *
*   the Free Software Foundation; either version 2 of the License, or     *
*   (at your option) any later version.                                   *
*                                                                         *
*   This program is distributed in the hope that it will be useful,       *
*   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
*   GNU General Public License for more details.                          *
*                                                                         *
*   You should have received a copy of the GNU General Public License     *
*   along with this program; if not, write to the                         *
*   Free Software Foundation, Inc.,                                       *
*   51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.          *
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#if !defined(M64P_MEMACCESS_H)
#define M64P_MEMACCESS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "m64p_types.h"

typedef  int8_t  s8;
typedef uint8_t  u8;
typedef  int16_t s16;
typedef uint16_t u16;
typedef  int32_t s32;
typedef uint32_t u32;
typedef  int64_t s64;
typedef uint64_t u64;

// #########################################################
// ## RDRam Memory
// #########################################################

typedef const u8*(*ptr_read_rdram_buffer)(u32 addr, u32 length);
#if defined(M64P_CORE_PROTOTYPES)
EXPORT const u8* CALL read_rdram_buffer(u32 addr, u32 length);
#endif

typedef u32(*ptr_read_rdram_32)(u32 addr);
#if defined(M64P_CORE_PROTOTYPES)
EXPORT u32 CALL read_rdram_32(u32 addr);
#endif

typedef u16(*ptr_read_rdram_16)(u32 addr);
#if defined(M64P_CORE_PROTOTYPES)
EXPORT u16 CALL read_rdram_16(u32 addr);
#endif

typedef u8(*ptr_read_rdram_8)(u32 addr);
#if defined(M64P_CORE_PROTOTYPES)
EXPORT u8 CALL read_rdram_8(u32 addr);
#endif

// -------------------------------------------

typedef void(*ptr_write_rdram_32)(u32 addr, u32 value);
#if defined(M64P_CORE_PROTOTYPES)
EXPORT void CALL write_rdram_32(u32 addr, u32 value);
#endif

typedef void(*ptr_write_rdram_16)(u32 addr, u16 value);
#if defined(M64P_CORE_PROTOTYPES)
EXPORT void CALL write_rdram_16(u32 addr, u16 value);
#endif

typedef void(*ptr_write_rdram_8)(u32 addr, u8 value);
#if defined(M64P_CORE_PROTOTYPES)
EXPORT void CALL write_rdram_8(u32 addr, u8 value);
#endif

// #########################################################
// ## Rom Memory
// #########################################################

typedef const u8*(*ptr_read_rom_buffer)(u32 addr, u32 length);
#if defined(M64P_CORE_PROTOTYPES)
EXPORT const unsigned char* CALL read_rom_buffer(u32 addr, u32 length);
#endif

typedef u32(*ptr_read_rom_32)(u32 addr);
#if defined(M64P_CORE_PROTOTYPES)
EXPORT u32 CALL read_rom_32(u32 addr);
#endif

typedef u16(*ptr_read_rom_16)(u32 addr);
#if defined(M64P_CORE_PROTOTYPES)
EXPORT u16 CALL read_rom_16(u32 addr);
#endif

typedef u8(*ptr_read_rom_8)(u32 addr);
#if defined(M64P_CORE_PROTOTYPES)
EXPORT u8 CALL read_rom_8(u32 addr);
#endif

// -------------------------------------------

typedef void(*ptr_write_rom_32)(u32 addr, u32 value);
#if defined(M64P_CORE_PROTOTYPES)
EXPORT void CALL write_rom_32(u32 addr, u32 value);
#endif

typedef void(*ptr_write_rom_16)(u32 addr, u16 value);
#if defined(M64P_CORE_PROTOTYPES)
EXPORT void CALL write_rom_16(u32 addr, u16 value);
#endif

typedef void(*ptr_write_rom_8)(u32 addr, u8 value);
#if defined(M64P_CORE_PROTOTYPES)
EXPORT void CALL write_rom_8(u32 addr, u8 value);
#endif

typedef void(*ptr_savestates_refresh_hack)(void);
#if defined(M64P_CORE_PROTOTYPES)
EXPORT void CALL savestates_refresh_hack(void);
#endif

#ifdef __cplusplus
}
#endif

#endif /* #define M64P_MEMACCESS_H */