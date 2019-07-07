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
#include "memory/memory.h"
#include "m64p_rdmem.h"
#include "ri/rdram.h"

EXPORT uint64 CALL read_rdmem_64(uint32 addr)
{
	return ((uint64)read_rdmem_32(addr) << 32) | (uint64)read_rdmem_32(addr + 4);
}

EXPORT uint64 CALL read_rdmem_64_unaligned(uint32 addr)
{
	uint64 w[2];

	w[0] = read_rdmem_32_unaligned(addr);
	w[1] = read_rdmem_32_unaligned(addr + 4);
	return (w[0] << 32) | w[1];
}

EXPORT void CALL write_rdmem_64(uint32 addr, uint64 value)
{
	write_rdmem_32(addr, (uint32)(value >> 32));
	write_rdmem_32(addr + 4, (uint32)(value & 0xFFFFFFFF));
}

EXPORT void CALL write_rdmem_64_unaligned(uint32 addr, uint64 value)
{
	write_rdmem_32_unaligned(addr, (uint32)(value >> 32));
	write_rdmem_32_unaligned(addr + 4, (uint32)(value & 0xFFFFFFFF));
}

EXPORT uint32 CALL read_rdmem_32(uint32 addr)
{
	uint32_t value = g_rdram[rdram_dram_address(addr)];
	if (&value == 0)
		return M64P_MEM_INVALID;
	return value;
}

EXPORT uint32 CALL read_rdmem_32_unaligned(uint32 addr)
{
	uint8 i, b[4];

	for (i = 0; i<4; i++) b[i] = read_rdmem_8(addr + i);
	return (b[0] << 24) | (b[1] << 16) | (b[2] << 8) | b[3];
}

EXPORT void CALL write_rdmem_32(uint32 addr, uint32 value)
{
	g_rdram[(addr & 0xffffff) >> 2] = value;
}

EXPORT void CALL write_rdmem_32_unaligned(uint32 addr, uint32 value)
{
	write_rdmem_8(addr + 0, value >> 24);
	write_rdmem_8(addr + 1, (value >> 16) & 0xFF);
	write_rdmem_8(addr + 2, (value >> 8) & 0xFF);
	write_rdmem_8(addr + 3, value & 0xFF);
}

//read_rdmem_16_unaligned and write_rdmem_16_unaligned don't exist because
//read_rdmem_16 and write_rdmem_16 work unaligned already.
EXPORT uint16 CALL read_rdmem_16(uint32 addr)
{
	return ((uint16)read_rdmem_8(addr) << 8) |
		(uint16)read_rdmem_8(addr + 1); //cough cough hack hack
}

EXPORT void CALL write_rdmem_16(uint32 addr, uint16 value)
{
	write_rdmem_8(addr, value >> 8); //this isn't much better
	write_rdmem_8(addr + 1, value & 0xFF); //then again, it works unaligned
}

EXPORT uint8 CALL read_rdmem_8(uint32 addr)
{
	uint32 word;

	word = read_rdmem_32(addr & ~3);
	return (word >> ((3 - (addr & 3)) * 8)) & 0xFF;
}

EXPORT void CALL write_rdmem_8(uint32 addr, uint8 value)
{
	uint32 word, mask;

	word = read_rdmem_32(addr & ~3);
	mask = 0xFF << ((3 - (addr & 3)) * 8);
	word = (word & ~mask) | (value << ((3 - (addr & 3)) * 8));
	write_rdmem_32(addr & ~3, word);
}