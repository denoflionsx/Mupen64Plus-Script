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

#include "main/main.h"
#include "main/savestates.h"
#include "memory/memory.h"
#include "m64p_memaccess.h"
#include "ri/rdram.h"

static u32 addr_align(u32 address)
{
	return (address & 0xffffff) >> 2;
}

// #########################################################
// ## RDRam Memory
// #########################################################

EXPORT const u8* CALL read_rdram_buffer(u32 addr, u32 length)
{
	const u8* value = malloc(length + 1);
	//size_t len = addr & 3;
	//size_t i;

	//// PreBlock
	//if (len > 0) {

	//}

	//// InBlock

	//// PostBlock

	u8 val;

	for (int i = 0; i < length; i++) {
		val = read_rdram_8(addr + i);
		memcpy(value + i, &val, 1);
	}

	return value;
}

EXPORT u32 CALL read_rdram_32(u32 addr)
{
	return (u32)g_rdram[addr_align(addr)];
}

EXPORT u16 CALL read_rdram_16(u32 addr)
{
	size_t offset = (addr_align(addr) * 4) + (3 - addr & 2);
	u16 value; memcpy(&value, (u8*)g_rdram + offset, 2);
	return value;
}

EXPORT u8 CALL read_rdram_8(u32 addr)
{
	size_t offset = (addr_align(addr) * 4) + (3 - addr & 3);
	u8 value; memcpy(&value, (u8*)g_rdram + offset, 1);
	return value;
}

// -------------------------------------------

EXPORT void CALL write_rdram_32(u32 addr, u32 value)
{
	size_t offset = addr_align(addr) * 4;
	memcpy((u8*)g_rdram + offset, &value, 4);
}

EXPORT void CALL write_rdram_16(u32 addr, u16 value)
{
	size_t offset = (addr_align(addr) * 4) + (3 - addr & 2);
	memcpy((u8*)g_rdram + offset, &value, 2);
}

EXPORT void CALL write_rdram_8(u32 addr, u8 value)
{
	size_t offset = (addr_align(addr) * 4) + (3 - addr & 3);
	memcpy((u8*)g_rdram + offset, &value, 1);
}

// #########################################################
// ## Rom Memory
// #########################################################

#ifdef WIN32
#include <stdlib.h>
#define __bswap_32(x) ((u32)_byteswap_ulong(x))
#define __bswap_16(x) ((u16)_byteswap_ushort(x))
#else
#define __bswap_32(x) ((u32)__builtin_bswap32(x))
#define __bswap_16(x) ((u16)__builtin_bswap16(x))
#endif

EXPORT const u8* CALL read_rom_buffer(u32 addr, u32 length)
{
	const u8* value = malloc(length + 1);
	memcpy(value, g_rom + addr, length);
	return value;
}

EXPORT u32 CALL read_rom_32(u32 addr)
{
	size_t offset = addr_align(addr) * 4;
	u32 value; memcpy(&value, g_rom + offset, 4);
	return (__bswap_32(value));
}

EXPORT u16 CALL read_rom_16(u32 addr)
{
	size_t offset = (addr_align(addr) * 4) + (addr & 2);
	u16 value; memcpy(&value, g_rom + offset, 2);
	return (__bswap_16(value));
}

EXPORT u8 CALL read_rom_8(u32 addr)
{
	return (u8)g_rom[addr];
}

// -------------------------------------------

EXPORT void CALL write_rom_32(u32 addr, u32 value)
{
	size_t offset = addr_align(addr) * 4;
	value = __bswap_32(value);
	memcpy(g_rom + offset, &value, 4);
}

EXPORT void CALL write_rom_16(u32 addr, u16 value)
{
	size_t offset = (addr_align(addr) * 4) + (addr & 2);
	value = __bswap_16(value);
	memcpy(g_rom + offset, &value, 2);
}

EXPORT void CALL write_rom_8(u32 addr, u8 value)
{
	g_rom[addr] = value;
}

// #########################################################
// ## Save State Stuff
// #########################################################

EXPORT void CALL savestates_refresh_hack(void) { savestates_hack_refresh(); }