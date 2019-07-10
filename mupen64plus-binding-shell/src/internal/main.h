/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *   Mupen64plus - main.h                                                  *
 *   Mupen64Plus homepage: http://code.google.com/p/mupen64plus/           *
 *   Copyright (C) 2009 Richard42                                          *
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

#ifndef __MAIN_H__
#define __MAIN_H__

#include "../cheat/cheat.h"

extern void DebugMessage(int level, const char *message, ...);
extern void DebugCallback(void *Context, int level, const char *message);

extern int  g_Verbose;

extern m64p_handle l_ConfigCore;
extern m64p_handle l_ConfigVideo;
extern m64p_handle l_ConfigUI;

extern const char *l_CoreLibPath;
extern const char *l_ConfigDirPath;
extern const char *l_ROMFilepath;
extern const char *l_SaveStatePath;
extern const char *l_DataDirPath;

extern int  *l_TestShotList;
extern int   l_TestShotIdx;
extern int   l_SaveOptions;
extern int   l_CoreCompareMode;

extern eCheatMode l_CheatMode;
extern char      *l_CheatNumList;

extern int EmuMain(bool async);

#endif /* __MAIN_H__ */