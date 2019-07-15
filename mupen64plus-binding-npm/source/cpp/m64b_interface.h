#ifndef _M64B_INTERFACE_
#define _M64B_INTERFACE_

#include <napi.h>
using namespace Napi;

// #########################################################
// ## Paths
// #########################################################

Value npmSetCoreLib(const CallbackInfo& info);
Value npmSetConfigDir(const CallbackInfo& info);
Value npmSetDataDir(const CallbackInfo& info);
Value npmSetPluginDir(const CallbackInfo& info);
Value npmSetPluginAudio(const CallbackInfo& info);
Value npmSetPluginGFX(const CallbackInfo& info);
Value npmSetPluginInput(const CallbackInfo& info);
Value npmSetPluginRSP(const CallbackInfo& info);

// #########################################################
// ## General Functions
// #########################################################

/*
EXPORT void CALL SetOsdEnabled(int boolVal);
EXPORT void CALL SetFullscreen(int boolVal);
EXPORT void CALL SetNoSpeedLimit(void);
EXPORT void CALL SetResolution(int xres, int yres);
EXPORT void CALL SetVerboseLog(int boolVal);
*/

// #########################################################
// ## Special Functions
// #########################################################

Number npmRunEmulator(const CallbackInfo& info);
Number npmRunEmulatorAsync(const CallbackInfo& info);
Value npmPauseEmulator(const CallbackInfo& info);
Value npmResumeEmulator(const CallbackInfo& info);
Value npmStopEmulator(const CallbackInfo& info);
    
// #########################################################
// ## NAPI Export
// #########################################################

Object M64B_Interface_Init(Env env, Object exports);

#endif