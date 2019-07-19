#include "../internal/core_interface.h"
#include "../internal/main.h"
#include "../plugin/plugin.h"
#include "m64p_binding_interface.h"

// #########################################################
// ## Paths
// #########################################################

EXPORT void CALL SetCoreLib(const char *input) {
	l_CoreLibPath = strdup(input);
}

EXPORT void CALL SetConfigDir(const char *input) {
	l_ConfigDirPath = strdup(input);
}

EXPORT void CALL SetDataDir(const char *input) {
#if !defined(SHAREDIR)
	l_DataDirPath = strdup(input);
#endif
}

EXPORT void CALL SetPluginDir(const char *input) {
	g_PluginDir = strdup(input);
}

EXPORT void CALL SetPluginAudio(const char *input) {
	g_AudioPlugin = strdup(input);
}

EXPORT void CALL SetPluginGFX(const char *input) {
	g_GfxPlugin = strdup(input);
}

EXPORT void CALL SetPluginInput(const char *input) {
	g_InputPlugin = strdup(input);
}

EXPORT void CALL SetPluginRSP(const char *input) {
	g_RspPlugin = strdup(input);
}

// #########################################################
// ## General Functions
// #########################################################

EXPORT void CALL SetOsdEnabled(int boolVal) {
	if (boolVal > 1) boolVal = 1;
	else if (boolVal < 0) boolVal = 0;
	(*ConfigSetParameter)(l_ConfigCore, "OnScreenDisplay", M64TYPE_BOOL, &boolVal);
}

EXPORT void CALL SetFullscreen(int boolVal) {
	if (boolVal > 1) boolVal = 1;
	else if (boolVal < 0) boolVal = 0;
	(*ConfigSetParameter)(l_ConfigVideo, "Fullscreen", M64TYPE_BOOL, &boolVal);
}

EXPORT void CALL SetNoSpeedLimit(void) {
	int EnableSpeedLimit = 0;
	if (g_CoreAPIVersion < 0x020001)
		DebugMessage(M64MSG_WARNING, "core library doesn't support --nospeedlimit");
	else
	{
		if ((*CoreDoCommand)(M64CMD_CORE_STATE_SET, M64CORE_SPEED_LIMITER, &EnableSpeedLimit) != M64ERR_SUCCESS)
			DebugMessage(M64MSG_ERROR, "core gave error while setting --nospeedlimit option");
	}
}

EXPORT void CALL SetResolution(int xres, int yres) {
	if (xres <= 0 || yres <= 0)
		DebugMessage(M64MSG_WARNING, "Resolution values must be greater than 0!");

	(*ConfigSetParameter)(l_ConfigVideo, "ScreenWidth", M64TYPE_INT, &xres);
	(*ConfigSetParameter)(l_ConfigVideo, "ScreenHeight", M64TYPE_INT, &yres);
}

EXPORT void CALL SetVerboseLog(int boolVal) {
	if (boolVal > 1) boolVal = 1;
	else if (boolVal < 0) boolVal = 0;
	g_Verbose = boolVal;
}

// #########################################################
// ## Special Functions
// #########################################################

EXPORT int CALL InitEmulator() {
	return Initialize();
}

EXPORT int CALL LoadRom(const char *romFile) {
	l_ROMFilepath = strdup(romFile);
	return LoadGame();
}

EXPORT int CALL RunEmulator(bool async) {
	return Boot(async);
}

EXPORT void CALL PauseEmulator(void) { (*CoreDoCommand)(M64CMD_PAUSE, 0, NULL); }
EXPORT void CALL ResumeEmulator(void) { (*CoreDoCommand)(M64CMD_RESUME, 0, NULL); }
EXPORT void CALL StopEmulator(void) { (*CoreDoCommand)(M64CMD_STOP, 0, NULL); }

EXPORT void CALL SetFrameCallback(void* ParamPtr) { (*CoreDoCommand)(M64CMD_SET_FRAME_CALLBACK, 0, ParamPtr); }

/*
static m64p_error ParseCommandLineFinal(int argc, const char **argv)
{
	int i;

	for (i = 1; i < argc; i++)
	{
		else if (strcmp(argv[i], "--cheats") == 0 && ArgsLeft >= 1)
		{
			if (strcmp(argv[i + 1], "all") == 0)
				l_CheatMode = CHEAT_ALL;
			else if (strcmp(argv[i + 1], "list") == 0)
				l_CheatMode = CHEAT_SHOW_LIST;
			else
			{
				l_CheatMode = CHEAT_LIST;
				l_CheatNumList = (char*)argv[i + 1];
			}
			i++;
		}
		else if (strcmp(argv[i], "--sshotdir") == 0 && ArgsLeft >= 1)
		{
			(*ConfigSetParameter)(l_ConfigCore, "ScreenshotPath", M64TYPE_STRING, argv[i + 1]);
			i++;
		}
		else if (strcmp(argv[i], "--emumode") == 0 && ArgsLeft >= 1)
		{
			int emumode = atoi(argv[i + 1]);
			i++;
			if (emumode < 0 || emumode > 2)
			{
				DebugMessage(M64MSG_WARNING, "invalid --emumode value '%i'", emumode);
				continue;
			}
			if (emumode == 2 && !(g_CoreCapabilities & M64CAPS_DYNAREC))
			{
				DebugMessage(M64MSG_WARNING, "Emulator core doesn't support Dynamic Recompiler.");
				emumode = 1;
			}
			(*ConfigSetParameter)(l_ConfigCore, "R4300Emulator", M64TYPE_INT, &emumode);
		}
		else if (strcmp(argv[i], "--savestate") == 0 && ArgsLeft >= 1)
		{
			l_SaveStatePath = argv[i + 1];
			i++;
		}
		else if (strcmp(argv[i], "--testshots") == 0 && ArgsLeft >= 1)
		{
			l_TestShotList = ParseNumberList(argv[i + 1], NULL);
			i++;
		}
		else if (strcmp(argv[i], "--set") == 0 && ArgsLeft >= 1)
		{
			if (SetConfigParameter(argv[i + 1]) != 0)
				return M64ERR_INPUT_INVALID;
			i++;
		}
		else if (strcmp(argv[i], "--lua") == 0 && ArgsLeft >= 1)
		{
			(*CoreDoCommand)(M64CMD_LOAD_LUA_SCRIPT, 0, (char*)argv[i + 1]);
			i++;
		}
		else if (strcmp(argv[i], "--python") == 0 && ArgsLeft >= 1)
		{
			(*CoreDoCommand)(M64CMD_LOAD_PYTHON_SCRIPT, 0, (char*)argv[i + 1]);
			i++;
		}
		else if (strcmp(argv[i], "--core-compare-send") == 0)
		{
			l_CoreCompareMode = 1;
		}
		else if (strcmp(argv[i], "--core-compare-recv") == 0)
		{
			l_CoreCompareMode = 2;
		}
		else if (strcmp(argv[i], "--nosaveoptions") == 0)
		{
			l_SaveOptions = 0;
		}
	}

}
*/