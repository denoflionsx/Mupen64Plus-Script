#if !defined(__M64P_BINDING_INTERFACE_H__)
#define __M64P_BINDING_INTERFACE_H__

#include "m64p_types.h"

#ifndef WIN32
#define bool _Bool
#endif

EXPORT void CALL SetCoreLib(const char *input);
EXPORT void CALL SetConfigDir(const char *input);
EXPORT void CALL SetDataDir(const char *input);
EXPORT void CALL SetPluginDir(const char *input);
EXPORT void CALL SetPluginAudio(const char *input);
EXPORT void CALL SetPluginGFX(const char *input);
EXPORT void CALL SetPluginInput(const char *input);
EXPORT void CALL SetPluginRSP(const char *input);

EXPORT void CALL SetOsdEnabled(int boolVal);
EXPORT void CALL SetFullscreen(int boolVal);
EXPORT void CALL SetNoSpeedLimit(void);
EXPORT void CALL SetResolution(int xres, int yres);
EXPORT void CALL SetVerboseLog(int boolVal);

EXPORT int CALL InitEmulator();
EXPORT int CALL LoadRom(const char *romFile);

EXPORT int CALL RunEmulator(bool async);
EXPORT void CALL PauseEmulator(void);
EXPORT void CALL ResumeEmulator(void);
EXPORT void CALL StopEmulator(void);

EXPORT void CALL SetFrameCallback(void* ParamPtr);

#endif