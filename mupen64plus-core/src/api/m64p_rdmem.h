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

#if !defined(M64P_RDMEM_H)
#define M64P_RDMEM_H

#ifdef __cplusplus
extern "C" {
#endif

#include "m64p_types.h"

typedef unsigned char       uint8;
typedef unsigned short      uint16;
typedef unsigned int        uint32;
typedef unsigned long long  uint64;

typedef  int8_t  s8;
typedef uint8_t  u8;
typedef  int16_t s16;
typedef uint16_t u16;
typedef  int32_t s32;
typedef uint32_t u32;
typedef  int64_t s64;
typedef uint64_t u64;

typedef uint64 (*ptr_read_rdmem_64)(uint32 addr);
#if defined(M64P_CORE_PROTOTYPES)
EXPORT uint64 CALL read_rdmem_64(uint32 addr);
#endif

typedef uint64(*ptr_read_rdmem_64_unaligned)(uint32 addr);
#if defined(M64P_CORE_PROTOTYPES)
EXPORT uint64 CALL read_rdmem_64_unaligned(uint32 addr);
#endif

typedef void(*ptr_write_rdmem_64)(uint32 addr, uint64 value);
#if defined(M64P_CORE_PROTOTYPES)
EXPORT void CALL write_rdmem_64(uint32 addr, uint64 value);
#endif

typedef void(*ptr_write_rdmem_64_unaligned)(uint32 addr, uint64 value);
#if defined(M64P_CORE_PROTOTYPES)
EXPORT void CALL write_rdmem_64_unaligned(uint32 addr, uint64 value);
#endif

typedef uint32(*ptr_read_rdmem_32)(uint32 addr);
#if defined(M64P_CORE_PROTOTYPES)
EXPORT uint32 CALL read_rdmem_32(uint32 addr);
#endif

typedef uint32(*ptr_read_rdmem_32_unaligned)(uint32 addr);
#if defined(M64P_CORE_PROTOTYPES)
EXPORT uint32 CALL read_rdmem_32_unaligned(uint32 addr);
#endif

typedef void(*ptr_write_rdmem_32)(uint32 addr, uint32 value);
#if defined(M64P_CORE_PROTOTYPES)
EXPORT void CALL write_rdmem_32(uint32 addr, uint32 value);
#endif

typedef void(*ptr_write_rdmem_32_unaligned)(uint32 addr, uint32 value);
#if defined(M64P_CORE_PROTOTYPES)
EXPORT void CALL write_rdmem_32_unaligned(uint32 addr, uint32 value);
#endif

typedef uint16(*ptr_read_rdmem_16)(uint32 addr);
#if defined(M64P_CORE_PROTOTYPES)
EXPORT uint16 CALL read_rdmem_16(uint32 addr);
#endif

typedef void(*ptr_write_rdmem_16)(uint32 addr, uint16 value);
#if defined(M64P_CORE_PROTOTYPES)
EXPORT void CALL write_rdmem_16(uint32 addr, uint16 value);
#endif

typedef uint8(*ptr_read_rdmem_8)(uint32 addr);
#if defined(M64P_CORE_PROTOTYPES)
EXPORT uint8 CALL read_rdmem_8(uint32 addr);
#endif

typedef void(*ptr_write_rdmem_8)(uint32 addr, uint8 value);
#if defined(M64P_CORE_PROTOTYPES)
EXPORT void CALL write_rdmem_8(uint32 addr, uint8 value);
#endif

#define CHECK_MEM(address) \
  if(!invalid_code[(address) >> 12] && blocks[(address) >> 12]->block[((address) & 0xFFF)/4].ops != current_instruction_table.NOTCOMPILED) \
    invalid_code[(address) >> 12]=1;

#ifdef __cplusplus
}
#endif

#endif /* #define M64P_RDMEM_H */