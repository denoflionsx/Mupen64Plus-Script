#if !defined(__M64B_H__)
#define __M64B_H__

#include "m64p_types.h"
#include "m64p_rdmem.h"

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

EXPORT int CALL RunEmulator(const char *romFile);


EXPORT uint64 CALL RdMemRead64(uint32 addr);
EXPORT uint64 CALL RdMemReadU64(uint32 addr);
EXPORT void CALL RdMemWrite64(uint32 addr, uint64 value);
EXPORT void CALL RdMemWriteU64(uint32 addr, uint64 value);
EXPORT uint32 CALL RdMemRead32(uint32 addr);
EXPORT uint32 CALL RdMemReadU32(uint32 addr);
EXPORT void CALL RdMemWrite32(uint32 addr, uint32 value);
EXPORT void CALL RdMemWriteU32(uint32 addr, uint32 value);
EXPORT uint16 CALL RdMemRead16(uint32 addr);
EXPORT void CALL RdMemWrite16(uint32 addr, uint16 value);
EXPORT uint8 CALL RdMemRead8(uint32 addr);
EXPORT void CALL RdMemWrite8(uint32 addr, uint8 value);

#endif