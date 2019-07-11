#include <napi.h>

namespace m64b_interface 
{

    // #########################################################
    // ## Paths
    // #########################################################

    Napi::Number WrapSetCoreLib(const Napi::CallbackInfo& info);
    Napi::Number WrapSetConfigDir(const Napi::CallbackInfo& info);
    Napi::Number WrapSetDataDir(const Napi::CallbackInfo& info);
    Napi::Number WrapSetPluginDir(const Napi::CallbackInfo& info);
    Napi::Number WrapSetPluginAudio(const Napi::CallbackInfo& info);
    Napi::Number WrapSetPluginGFX(const Napi::CallbackInfo& info);
    Napi::Number WrapSetPluginInput(const Napi::CallbackInfo& info);
    Napi::Number WrapSetPluginRSP(const Napi::CallbackInfo& info);

    // #########################################################
    // ## Functions
    // #########################################################

    /*
    EXPORT void CALL SetOsdEnabled(int boolVal);
    EXPORT void CALL SetFullscreen(int boolVal);
    EXPORT void CALL SetNoSpeedLimit(void);
    EXPORT void CALL SetResolution(int xres, int yres);
    EXPORT void CALL SetVerboseLog(int boolVal);
    */

    Napi::Number WrapRunEmulator(const Napi::CallbackInfo& info);
    Napi::Number WrapRunEmulatorAsync(const Napi::CallbackInfo& info);
    Napi::Number WrapPauseEmulator(const Napi::CallbackInfo& info);
    Napi::Number WrapResumeEmulator(const Napi::CallbackInfo& info);
    Napi::Number WrapStopEmulator(const Napi::CallbackInfo& info);

    // #########################################################
    // ## NAPI Export
    // #########################################################

    Napi::Object Init(Napi::Env env, Napi::Object exports);

}