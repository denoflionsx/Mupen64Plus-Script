/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *   Mupen64plus-ui-console - main.c                                       *
 *   Mupen64Plus homepage: http://code.google.com/p/mupen64plus/           *
 *   Copyright (C) 2007-2010 Richard42                                     *
 *   Copyright (C) 2008 Ebenblues Nmn Okaygo Tillin9                       *
 *   Copyright (C) 2002 Hacktarux                                          *
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

 /* This is the main application entry point for the console-only front-end
  * for Mupen64Plus v2.0.
  */

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "SDL_main.h"
#include "../cheat/cheat.h"
#include "compare_core.h"
#include "core_interface.h"
#include "m64p_types.h"
#include "main.h"
#include "../osal/osal_preproc.h"
#include "../plugin/plugin.h"
#include "version.h"

  /* Version number for Binding-Shell config section parameters */
#define CONFIG_PARAM_VERSION     1.00

/* Fix for legacy functions called by SDLmain.lib */
extern "C" { FILE __iob_func[3] = { *stdin,*stdout,*stderr }; }
#pragma comment(lib, "legacy_stdio_definitions.lib")

/** global variables **/
int    g_Verbose = 0;

/** static (local) variables **/
m64p_handle l_ConfigCore = NULL;
m64p_handle l_ConfigVideo = NULL;
m64p_handle l_ConfigUI = NULL;

const char *l_CoreLibPath = NULL;
const char *l_ConfigDirPath = NULL;
const char *l_ROMFilepath = NULL;       // filepath of ROM to load & run at startup
const char *l_SaveStatePath = NULL;     // save state to load at startup

#if defined(SHAREDIR)
const char *l_DataDirPath = SHAREDIR;
#else
const char *l_DataDirPath = NULL;
#endif

int  *l_TestShotList = NULL;      // list of screenshots to take for regression test support
int   l_TestShotIdx = 0;          // index of next screenshot frame in list
int   l_SaveOptions = 1;          // save command-line options in configuration file (enabled by default)
int   l_CoreCompareMode = 0;      // 0 = disable, 1 = send, 2 = receive

eCheatMode l_CheatMode = CHEAT_DISABLE;
char      *l_CheatNumList = NULL;

/*********************************************************************************************************
 *  Callback functions from the core
 */

void DebugMessage(int level, const char *message, ...)
{
	char msgbuf[1024];
	va_list args;

	va_start(args, message);
	vsnprintf(msgbuf, 1024, message, args);

	DebugCallback("Binding-Shell", level, msgbuf);

	va_end(args);
}

void DebugCallback(void *Context, int level, const char *message)
{
#ifdef ANDROID
	if (level == M64MSG_ERROR)
		__android_log_print(ANDROID_LOG_ERROR, (const char *)Context, "%s", message);
	else if (level == M64MSG_WARNING)
		__android_log_print(ANDROID_LOG_WARN, (const char *)Context, "%s", message);
	else if (level == M64MSG_INFO)
		__android_log_print(ANDROID_LOG_INFO, (const char *)Context, "%s", message);
	else if (level == M64MSG_STATUS)
		__android_log_print(ANDROID_LOG_DEBUG, (const char *)Context, "%s", message);
	else if (level == M64MSG_VERBOSE)
	{
		if (g_Verbose)
			__android_log_print(ANDROID_LOG_VERBOSE, (const char *)Context, "%s", message);
	}
	else
		__android_log_print(ANDROID_LOG_ERROR, (const char *)Context, "Unknown: %s", message);
#else
	if (level == M64MSG_ERROR)
		printf("%s Error: %s\n", (const char *)Context, message);
	else if (level == M64MSG_WARNING)
		printf("%s Warning: %s\n", (const char *)Context, message);
	else if (level == M64MSG_INFO)
		printf("%s: %s\n", (const char *)Context, message);
	else if (level == M64MSG_STATUS)
		printf("%s Status: %s\n", (const char *)Context, message);
	else if (level == M64MSG_VERBOSE)
	{
		if (g_Verbose)
			printf("%s: %s\n", (const char *)Context, message);
	}
	else
		printf("%s Unknown: %s\n", (const char *)Context, message);
#endif
}

static void FrameCallback(unsigned int FrameIndex)
{
	// load savestate at first frame if needed
	if (l_SaveStatePath != NULL && FrameIndex == 0)
	{
		if ((*CoreDoCommand)(M64CMD_STATE_LOAD, 0, (void *)l_SaveStatePath) != M64ERR_SUCCESS)
		{
			DebugMessage(M64MSG_WARNING, "couldn't load state, rom will run normally.");
		}
	}

	// take a screenshot if we need to
	if (l_TestShotList != NULL)
	{
		int nextshot = l_TestShotList[l_TestShotIdx];
		if (nextshot == FrameIndex)
		{
			(*CoreDoCommand)(M64CMD_TAKE_NEXT_SCREENSHOT, 0, NULL);  /* tell the core take a screenshot */
			// advance list index to next screenshot frame number.  If it's 0, then quit
			l_TestShotIdx++;
		}
		else if (nextshot == 0)
		{
			(*CoreDoCommand)(M64CMD_STOP, 0, NULL);  /* tell the core to shut down ASAP */
			free(l_TestShotList);
			l_TestShotList = NULL;
		}
	}
}

/*********************************************************************************************************
 *  Configuration handling
 */

static m64p_error OpenConfigurationHandles(void)
{
	float fConfigParamsVersion;
	int bSaveConfig = 0;
	m64p_error rval;

	/* Open Configuration sections for core library and console User Interface */
	rval = (*ConfigOpenSection)("Core", &l_ConfigCore);
	if (rval != M64ERR_SUCCESS)
	{
		DebugMessage(M64MSG_ERROR, "failed to open 'Core' configuration section");
		return rval;
	}

	rval = (*ConfigOpenSection)("Video-General", &l_ConfigVideo);
	if (rval != M64ERR_SUCCESS)
	{
		DebugMessage(M64MSG_ERROR, "failed to open 'Video-General' configuration section");
		return rval;
	}

	rval = (*ConfigOpenSection)("Binding-Shell", &l_ConfigUI);
	if (rval != M64ERR_SUCCESS)
	{
		DebugMessage(M64MSG_ERROR, "failed to open 'Binding-Shell' configuration section");
		return rval;
	}

	if ((*ConfigGetParameter)(l_ConfigUI, "Version", M64TYPE_FLOAT, &fConfigParamsVersion, sizeof(float)) != M64ERR_SUCCESS)
	{
		DebugMessage(M64MSG_WARNING, "No version number in 'Binding-Shell' config section. Setting defaults.");
		(*ConfigDeleteSection)("Binding-Shell");
		(*ConfigOpenSection)("Binding-Shell", &l_ConfigUI);
		bSaveConfig = 1;
	}
	else if (((int)fConfigParamsVersion) != ((int)CONFIG_PARAM_VERSION))
	{
		DebugMessage(M64MSG_WARNING, "Incompatible version %.2f in 'Binding-Shell' config section: current is %.2f. Setting defaults.", fConfigParamsVersion, (float)CONFIG_PARAM_VERSION);
		(*ConfigDeleteSection)("Binding-Shell");
		(*ConfigOpenSection)("Binding-Shell", &l_ConfigUI);
		bSaveConfig = 1;
	}
	else if ((CONFIG_PARAM_VERSION - fConfigParamsVersion) >= 0.0001f)
	{
		/* handle upgrades */
		float fVersion = CONFIG_PARAM_VERSION;
		ConfigSetParameter(l_ConfigUI, "Version", M64TYPE_FLOAT, &fVersion);
		DebugMessage(M64MSG_INFO, "Updating parameter set version in 'Binding-Shell' config section to %.2f", fVersion);
		bSaveConfig = 1;
	}

	/* Set default values for my Config parameters */
	(*ConfigSetDefaultFloat)(l_ConfigUI, "Version", CONFIG_PARAM_VERSION, "Mupen64Plus Binding-Shell config parameter set version number.  Please don't change this version number.");
	(*ConfigSetDefaultString)(l_ConfigUI, "PluginDir", OSAL_CURRENT_DIR, "Directory in which to search for plugins");
	(*ConfigSetDefaultString)(l_ConfigUI, "VideoPlugin", "mupen64plus-video-rice" OSAL_DLL_EXTENSION, "Filename of video plugin");
	(*ConfigSetDefaultString)(l_ConfigUI, "AudioPlugin", "mupen64plus-audio-sdl" OSAL_DLL_EXTENSION, "Filename of audio plugin");
	(*ConfigSetDefaultString)(l_ConfigUI, "InputPlugin", "mupen64plus-input-sdl" OSAL_DLL_EXTENSION, "Filename of input plugin");
	(*ConfigSetDefaultString)(l_ConfigUI, "RspPlugin", "mupen64plus-rsp-hle" OSAL_DLL_EXTENSION, "Filename of RSP plugin");

	if (bSaveConfig && ConfigSaveSection != NULL) /* ConfigSaveSection was added in Config API v2.1.0 */
		(*ConfigSaveSection)("Binding-Shell");

	return M64ERR_SUCCESS;
}

static m64p_error SaveConfigurationOptions(void)
{
	/* if shared data directory was given on the command line, write it into the config file */
	if (l_DataDirPath != NULL)
		(*ConfigSetParameter)(l_ConfigCore, "SharedDataPath", M64TYPE_STRING, l_DataDirPath);

	/* if any plugin filepaths were given on the command line, write them into the config file */
	if (g_PluginDir != NULL)
		(*ConfigSetParameter)(l_ConfigUI, "PluginDir", M64TYPE_STRING, g_PluginDir);
	if (g_GfxPlugin != NULL)
		(*ConfigSetParameter)(l_ConfigUI, "VideoPlugin", M64TYPE_STRING, g_GfxPlugin);
	if (g_AudioPlugin != NULL)
		(*ConfigSetParameter)(l_ConfigUI, "AudioPlugin", M64TYPE_STRING, g_AudioPlugin);
	if (g_InputPlugin != NULL)
		(*ConfigSetParameter)(l_ConfigUI, "InputPlugin", M64TYPE_STRING, g_InputPlugin);
	if (g_RspPlugin != NULL)
		(*ConfigSetParameter)(l_ConfigUI, "RspPlugin", M64TYPE_STRING, g_RspPlugin);

	return (*ConfigSaveFile)();
}

/*********************************************************************************************************
 *  Command-line parsing
 */

static void printUsage(const char *progname)
{
	printf("Usage: %s [parameters] [romfile]\n"
		"\n"
		"Parameters:\n"
		"    --noosd                : disable onscreen display\n"
		"    --osd                  : enable onscreen display\n"
		"    --fullscreen           : use fullscreen display mode\n"
		"    --windowed             : use windowed display mode\n"
		"    --resolution (res)     : display resolution (640x480, 800x600, 1024x768, etc)\n"
		"    --nospeedlimit         : disable core speed limiter (should be used with dummy audio plugin)\n"
		"    --cheats (cheat-spec)  : enable or list cheat codes for the given rom file\n"
		"    --corelib (filepath)   : use core library (filepath) (can be only filename or full path)\n"
		"    --configdir (dir)      : force configation directory to (dir); should contain mupen64plus.cfg\n"
		"    --datadir (dir)        : search for shared data files (.ini files, languages, etc) in (dir)\n"
		"    --plugindir (dir)      : search for plugins in (dir)\n"
		"    --sshotdir (dir)       : set screenshot directory to (dir)\n"
		"    --gfx (plugin-spec)    : use gfx plugin given by (plugin-spec)\n"
		"    --audio (plugin-spec)  : use audio plugin given by (plugin-spec)\n"
		"    --input (plugin-spec)  : use input plugin given by (plugin-spec)\n"
		"    --rsp (plugin-spec)    : use rsp plugin given by (plugin-spec)\n"
		"    --emumode (mode)       : set emu mode to: 0=Pure Interpreter 1=Interpreter 2=DynaRec\n"
		"    --savestate (filepath) : savestate loaded at startup\n"
		"    --testshots (list)     : take screenshots at frames given in comma-separated (list), then quit\n"
		"    --set (param-spec)     : set a configuration variable, format: ParamSection[ParamName]=Value\n"
		"    --core-compare-send    : use the Core Comparison debugging feature, in data sending mode\n"
		"    --core-compare-recv    : use the Core Comparison debugging feature, in data receiving mode\n"
		"    --lua (filepath)        : load specified Lua script at start\n"
		"    --python (filepath)        : load specified Python script at start\n"
		"    --nosaveoptions        : do not save the given command-line options in configuration file\n"
		"    --verbose              : print lots of information\n"
		"    --help                 : see this help message\n\n"
		"(plugin-spec):\n"
		"    (pluginname)           : filename (without path) of plugin to find in plugin directory\n"
		"    (pluginpath)           : full path and filename of plugin\n"
		"    'dummy'                : use dummy plugin\n\n"
		"(cheat-spec):\n"
		"    'list'                 : show all of the available cheat codes\n"
		"    'all'                  : enable all of the available cheat codes\n"
		"    (codelist)             : a comma-separated list of cheat code numbers to enable,\n"
		"                             with dashes to use code variables (ex 1-2 to use cheat 1 option 2)\n"
		"\n", progname);

	return;
}

static int SetConfigParameter(const char *ParamSpec)
{
	char *ParsedString, *VarName, *VarValue = NULL;
	m64p_handle ConfigSection;
	m64p_type VarType;
	m64p_error rval;

	if (ParamSpec == NULL)
	{
		DebugMessage(M64MSG_ERROR, "ParamSpec is NULL in SetConfigParameter()");
		return 1;
	}

	/* make a copy of the input string */
	ParsedString = (char *)malloc(strlen(ParamSpec) + 1);
	if (ParsedString == NULL)
	{
		DebugMessage(M64MSG_ERROR, "SetConfigParameter() couldn't allocate memory for temporary string.");
		return 2;
	}
	strcpy(ParsedString, ParamSpec);

	/* parse it for the simple section[name]=value format */
	VarName = strchr(ParsedString, '[');
	if (VarName != NULL)
	{
		*VarName++ = 0;
		VarValue = strchr(VarName, ']');
		if (VarValue != NULL)
		{
			*VarValue++ = 0;
		}
	}
	if (VarName == NULL || VarValue == NULL || *VarValue != '=')
	{
		DebugMessage(M64MSG_ERROR, "invalid (param-spec) '%s'", ParamSpec);
		free(ParsedString);
		return 3;
	}
	VarValue++;

	/* then set the value */
	rval = (*ConfigOpenSection)(ParsedString, &ConfigSection);
	if (rval != M64ERR_SUCCESS)
	{
		DebugMessage(M64MSG_ERROR, "SetConfigParameter failed to open config section '%s'", ParsedString);
		free(ParsedString);
		return 4;
	}
	if ((*ConfigGetParameterType)(ConfigSection, VarName, &VarType) == M64ERR_SUCCESS)
	{
		switch (VarType)
		{
			int ValueInt;
			float ValueFloat;
		case M64TYPE_INT:
			ValueInt = atoi(VarValue);
			ConfigSetParameter(ConfigSection, VarName, M64TYPE_INT, &ValueInt);
			break;
		case M64TYPE_FLOAT:
			ValueFloat = (float)atof(VarValue);
			ConfigSetParameter(ConfigSection, VarName, M64TYPE_FLOAT, &ValueFloat);
			break;
		case M64TYPE_BOOL:
			ValueInt = (int)(osal_insensitive_strcmp(VarValue, "true") == 0);
			ConfigSetParameter(ConfigSection, VarName, M64TYPE_BOOL, &ValueInt);
			break;
		case M64TYPE_STRING:
			ConfigSetParameter(ConfigSection, VarName, M64TYPE_STRING, VarValue);
			break;
		default:
			DebugMessage(M64MSG_ERROR, "invalid VarType in SetConfigParameter()");
			return 5;
		}
	}
	else
	{
		ConfigSetParameter(ConfigSection, VarName, M64TYPE_STRING, VarValue);
	}

	free(ParsedString);
	return 0;
}

static int *ParseNumberList(const char *InputString, int *ValuesFound)
{
	const char *str;
	int *OutputList;

	/* count the number of integers in the list */
	int values = 1;
	str = InputString;
	while ((str = strchr(str, ',')) != NULL)
	{
		str++;
		values++;
	}

	/* create a list and populate it with the frame counter values at which to take screenshots */
	if ((OutputList = (int *)malloc(sizeof(int) * (values + 1))) != NULL)
	{
		int idx = 0;
		str = InputString;
		while (str != NULL)
		{
			OutputList[idx++] = atoi(str);
			str = strchr(str, ',');
			if (str != NULL) str++;
		}
		OutputList[idx] = 0;
	}

	if (ValuesFound != NULL)
		*ValuesFound = values;
	return OutputList;
}

/*********************************************************************************************************
* main function
*/

/* Allow state callback in external module to be specified via build flags (header and function name) */
#ifdef CALLBACK_HEADER
#define xstr(s) str(s)
#define str(s) #s
#include xstr(CALLBACK_HEADER)
#endif

#ifndef CALLBACK_FUNC
#define CALLBACK_FUNC NULL
#endif

void KillEmuProc(void) {
	int i;

	/* detach plugins from core and unload them */
	for (i = 0; i < 4; i++)
		(*CoreDetachPlugin)(g_PluginMap[i].type);
	PluginUnload();

	/* close the ROM image */
	(*CoreDoCommand)(M64CMD_ROM_CLOSE, 0, NULL);

	/* save the configuration file again if --nosaveoptions was not specified, to keep any updated parameters from the core/plugins */
	if (l_SaveOptions)
		SaveConfigurationOptions();

	/* Shut down and release the Core library */
	(*CoreShutdown)();
	DetachCoreLib();

	/* free allocated memory */
	if (l_TestShotList != NULL)
		free(l_TestShotList);
}

#ifndef WIN32
/* Allow external modules to call the main function as a library method.  This is useful for user
 * interfaces that simply layer on top of (rather than re-implement) Binding-Shell (e.g. mupen64plus-ae).
 */
__attribute__((visibility("default")))

#else

// Thread stuff here.
DWORD WINAPI ExecuteM64PThread(void* data) {
	(*CoreDoCommand)(M64CMD_EXECUTE, 0, NULL);
	KillEmuProc();
	return 0;
}

#endif

int Initialize() {
	/* load the Mupen64Plus core library */
	if (AttachCoreLib(l_CoreLibPath) != M64ERR_SUCCESS)
		return 1;

	/* start the Mupen64Plus core library, load the configuration file */
	m64p_error rval = (*CoreStartup)(CORE_API_VERSION, l_ConfigDirPath, l_DataDirPath, "Core", DebugCallback, NULL, CALLBACK_FUNC);
	if (rval != M64ERR_SUCCESS)
	{
		DebugMessage(M64MSG_ERROR, "couldn't start Mupen64Plus core library.");
		DetachCoreLib();
		return 2;
	}

	/* Open configuration sections */
	rval = OpenConfigurationHandles();
	if (rval != M64ERR_SUCCESS)
	{
		(*CoreShutdown)();
		DetachCoreLib();
		return 3;
	}

	/* Handle the core comparison feature */
	if (l_CoreCompareMode != 0 && !(g_CoreCapabilities & M64CAPS_CORE_COMPARE))
	{
		DebugMessage(M64MSG_ERROR, "can't use --core-compare feature with this Mupen64Plus core library.");
		DetachCoreLib();
		return 4;
	}
	compare_core_init(l_CoreCompareMode);

	/* save the given command-line options in configuration file if requested */
	if (l_SaveOptions)
		SaveConfigurationOptions();
}

int LoadGame() {
	/* load ROM image */
	FILE *fPtr = fopen(l_ROMFilepath, "rb");
	if (fPtr == NULL)
	{
		DebugMessage(M64MSG_ERROR, "couldn't open ROM file '%s' for reading.", l_ROMFilepath);
		(*CoreShutdown)();
		DetachCoreLib();
		return 1;
	}
	/* get the length of the ROM, allocate memory buffer, load it from disk */
	long romlength = 0;
	fseek(fPtr, 0L, SEEK_END);
	romlength = ftell(fPtr);
	fseek(fPtr, 0L, SEEK_SET);
	unsigned char *ROM_buffer = (unsigned char *)malloc(romlength);
	if (ROM_buffer == NULL)
	{
		DebugMessage(M64MSG_ERROR, "couldn't allocate %li-byte buffer for ROM image file '%s'.", romlength, l_ROMFilepath);
		fclose(fPtr);
		(*CoreShutdown)();
		DetachCoreLib();
		return 2;
	}
	else if (fread(ROM_buffer, 1, romlength, fPtr) != romlength)
	{
		DebugMessage(M64MSG_ERROR, "couldn't read %li bytes from ROM image file '%s'.", romlength, l_ROMFilepath);
		free(ROM_buffer);
		fclose(fPtr);
		(*CoreShutdown)();
		DetachCoreLib();
		return 3;
	}
	fclose(fPtr);

	/* Try to load the ROM image into the core */
	if ((*CoreDoCommand)(M64CMD_ROM_OPEN, (int)romlength, ROM_buffer) != M64ERR_SUCCESS)
	{
		DebugMessage(M64MSG_ERROR, "core failed to open ROM image file '%s'.", l_ROMFilepath);
		free(ROM_buffer);
		(*CoreShutdown)();
		DetachCoreLib();
		return 4;
	}
	free(ROM_buffer); /* the core copies the ROM image, so we can release this buffer immediately */
	return 0;
}

int Boot(bool async)
{
	int i;

	printf(" __  __                         __   _  _   ____  _             \n");
	printf("|  \\/  |_   _ _ __   ___ _ __  / /_ | || | |  _ \\| |_   _ ___ \n");
	printf("| |\\/| | | | | '_ \\ / _ \\ '_ \\| '_ \\| || |_| |_) | | | | / __|  \n");
	printf("| |  | | |_| | |_) |  __/ | | | (_) |__   _|  __/| | |_| \\__ \\  \n");
	printf("|_|  |_|\\__,_| .__/ \\___|_| |_|\\___/   |_| |_|   |_|\\__,_|___/  \n");
	printf("             |_|         http://code.google.com/p/mupen64plus/  \n");
	printf("Binding Version %i.%i.%i\n\n", VERSION_PRINTF_SPLIT(CONSOLE_UI_VERSION));
	
	/* handle the cheat codes */
	CheatStart(l_CheatMode, l_CheatNumList);
	if (l_CheatMode == CHEAT_SHOW_LIST)
	{
		(*CoreDoCommand)(M64CMD_ROM_CLOSE, 0, NULL);
		(*CoreShutdown)();
		DetachCoreLib();
		return 1;
	}

	/* search for and load plugins */
	m64p_error rval = PluginSearchLoad(l_ConfigUI);
	if (rval != M64ERR_SUCCESS)
	{
		(*CoreDoCommand)(M64CMD_ROM_CLOSE, 0, NULL);
		(*CoreShutdown)();
		DetachCoreLib();
		return 2;
	}

	/* attach plugins to core */
	for (i = 0; i < 4; i++)
	{
		if ((*CoreAttachPlugin)(g_PluginMap[i].type, g_PluginMap[i].handle) != M64ERR_SUCCESS)
		{
			DebugMessage(M64MSG_ERROR, "core error while attaching %s plugin.", g_PluginMap[i].name);
			(*CoreDoCommand)(M64CMD_ROM_CLOSE, 0, NULL);
			(*CoreShutdown)();
			DetachCoreLib();
			return 3;
		}
	}

	/* set up Frame Callback if --testshots or --savestate is enabled */
	if (l_TestShotList != NULL || l_SaveStatePath != NULL)
	{
		if ((*CoreDoCommand)(M64CMD_SET_FRAME_CALLBACK, 0, FrameCallback) != M64ERR_SUCCESS)
		{
			DebugMessage(M64MSG_WARNING, "couldn't set frame callback, --testshots and/or --savestate will not work.");
		}
	}

	/* run the game */
	if (async) {
#ifdef WIN32
		HANDLE thread = CreateThread(NULL, 0, ExecuteM64PThread, NULL, 0, NULL);
		if (thread == NULL) printf("Failed to start M64P Async process.\n");
#endif
		return 0;
	}

	(*CoreDoCommand)(M64CMD_EXECUTE, 0, NULL);
	KillEmuProc();
	return 0;
}