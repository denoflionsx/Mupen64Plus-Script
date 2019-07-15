#include "m64b_interface.h"
#include <m64p_binding_interface.h>

// #########################################################
// ## Paths
// #########################################################

Value npmSetCoreLib(const CallbackInfo& info) {
    std::string input = info[0].As<String>().Utf8Value();
    SetCoreLib(input.c_str());
    return info.Env().Undefined();
}

Value npmSetConfigDir(const CallbackInfo& info) {
    std::string input = info[0].As<String>().Utf8Value();
    SetConfigDir(input.c_str());
    return info.Env().Undefined();
}

Value npmSetDataDir(const CallbackInfo& info) {
    std::string input = info[0].As<String>().Utf8Value();
    SetDataDir(input.c_str());
    return info.Env().Undefined();
}

Value npmSetPluginDir(const CallbackInfo& info) {
    std::string input = info[0].As<String>().Utf8Value();
    SetPluginDir(input.c_str());
    return info.Env().Undefined();
}

Value npmSetPluginAudio(const CallbackInfo& info) {
    std::string input = info[0].As<String>().Utf8Value();
    SetPluginAudio(input.c_str());
    return info.Env().Undefined();
}

Value npmSetPluginGFX(const CallbackInfo& info) {
    std::string input = info[0].As<String>().Utf8Value();
    SetPluginGFX(input.c_str());
    return info.Env().Undefined();
}

Value npmSetPluginInput(const CallbackInfo& info) {
    std::string input = info[0].As<String>().Utf8Value();
    SetPluginInput(input.c_str());
    return info.Env().Undefined();
}

Value npmSetPluginRSP(const CallbackInfo& info) {
    std::string input = info[0].As<String>().Utf8Value();
    SetPluginRSP(input.c_str());
    return info.Env().Undefined();
}

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

Number npmRunEmulator(const CallbackInfo& info) {
    std::string input = info[0].As<String>().Utf8Value();
    int ret = RunEmulator(input.c_str());
    return Number::New(info.Env(), ret);
}

Number npmRunEmulatorAsync(const CallbackInfo& info) {
    std::string input = info[0].As<String>().Utf8Value();
    int ret = RunEmulatorAsync(input.c_str());
    return Number::New(info.Env(), ret);
}

Value npmPauseEmulator(const CallbackInfo& info) {
    PauseEmulator();
    return info.Env().Undefined();
}

Value npmResumeEmulator(const CallbackInfo& info) {
    ResumeEmulator();
    return info.Env().Undefined();
}

Value npmStopEmulator(const CallbackInfo& info) {
    StopEmulator();
    return info.Env().Undefined();
}

// #########################################################
// ## NAPI Export
// #########################################################

Object M64B_Interface_Init(Env env, Object exports) {
    
    // Paths
    exports.Set("setCoreLib", Function::New(env, npmSetCoreLib));
    exports.Set("setConfigDir", Function::New(env, npmSetConfigDir));
    exports.Set("setDataDir", Function::New(env, npmSetDataDir));    
    exports.Set("setPluginDir", Function::New(env, npmSetPluginDir));
    exports.Set("setPluginAudio", Function::New(env, npmSetPluginAudio));
    exports.Set("setPluginGFX", Function::New(env, npmSetPluginGFX));
    exports.Set("setPluginInput", Function::New(env, npmSetPluginInput));
    exports.Set("setPluginRSP", Function::New(env, npmSetPluginRSP));
    
    // General Functions
    
    // Special Functions
    exports.Set("runEmulator", Function::New(env, npmRunEmulator));
    exports.Set("runEmulatorAsync", Function::New(env, npmRunEmulatorAsync));
    exports.Set("pauseEmulator", Function::New(env, npmPauseEmulator));
    exports.Set("resumeEmulator", Function::New(env, npmResumeEmulator));
    exports.Set("stopEmulator", Function::New(env, npmStopEmulator));
    
    return exports;
}