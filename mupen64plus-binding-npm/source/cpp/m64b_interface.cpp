#include <napi.h>
#include <m64p_binding_interface.h>
#include "m64b_interface.h"

// #########################################################
// ## Paths
// #########################################################

Napi::Number m64b_interface::WrapSetCoreLib(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();

    std::string input = info[0].As<Napi::String>().Utf8Value();
    SetCoreLib(input.c_str());

    return Napi::Number::New(env, 0);
}

Napi::Number m64b_interface::WrapSetConfigDir(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();

    std::string input = info[0].As<Napi::String>().Utf8Value();
    SetConfigDir(input.c_str());

    return Napi::Number::New(env, 0);
}

Napi::Number m64b_interface::WrapSetDataDir(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();

    std::string input = info[0].As<Napi::String>().Utf8Value();
    SetDataDir(input.c_str());

    return Napi::Number::New(env, 0);
}

Napi::Number m64b_interface::WrapSetPluginDir(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();

    std::string input = info[0].As<Napi::String>().Utf8Value();
    SetPluginDir(input.c_str());

    return Napi::Number::New(env, 0);
}

Napi::Number m64b_interface::WrapSetPluginAudio(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();

    std::string input = info[0].As<Napi::String>().Utf8Value();
    SetPluginAudio(input.c_str());

    return Napi::Number::New(env, 0);
}

Napi::Number m64b_interface::WrapSetPluginGFX(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();

    std::string input = info[0].As<Napi::String>().Utf8Value();
    SetPluginGFX(input.c_str());

    return Napi::Number::New(env, 0);
}

Napi::Number m64b_interface::WrapSetPluginInput(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();

    std::string input = info[0].As<Napi::String>().Utf8Value();
    SetPluginInput(input.c_str());

    return Napi::Number::New(env, 0);
}

Napi::Number m64b_interface::WrapSetPluginRSP(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();

    std::string input = info[0].As<Napi::String>().Utf8Value();
    SetPluginRSP(input.c_str());

    return Napi::Number::New(env, 0);
}

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

Napi::Number m64b_interface::WrapRunEmulator(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();

    std::string input = info[0].As<Napi::String>().Utf8Value();
    int ret = RunEmulator(input.c_str());

    return Napi::Number::New(env, ret);
}

Napi::Number m64b_interface::WrapRunEmulatorAsync(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();

    std::string input = info[0].As<Napi::String>().Utf8Value();
    int ret = RunEmulatorAsync(input.c_str());

    return Napi::Number::New(env, ret);
}

Napi::Number m64b_interface::WrapPauseEmulator(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    PauseEmulator();
    return Napi::Number::New(env, 0);
}

Napi::Number m64b_interface::WrapResumeEmulator(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    ResumeEmulator();
    return Napi::Number::New(env, 0);
}

Napi::Number m64b_interface::WrapStopEmulator(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    StopEmulator();
    return Napi::Number::New(env, 0);
}

// #########################################################
// ## NAPI Export
// #########################################################

Napi::Object m64b_interface::Init(Napi::Env env, Napi::Object exports) {
    
    // Paths
    exports.Set("setCoreLib", Napi::Function::New(env, m64b_interface::WrapSetCoreLib));
    exports.Set("setConfigDir", Napi::Function::New(env, m64b_interface::WrapSetConfigDir));
    exports.Set("setDataDir", Napi::Function::New(env, m64b_interface::WrapSetDataDir));    
    exports.Set("setPluginDir", Napi::Function::New(env, m64b_interface::WrapSetPluginDir));
    exports.Set("setPluginAudio", Napi::Function::New(env, m64b_interface::WrapSetPluginAudio));
    exports.Set("setPluginGFX", Napi::Function::New(env, m64b_interface::WrapSetPluginGFX));
    exports.Set("setPluginInput", Napi::Function::New(env, m64b_interface::WrapSetPluginInput));
    exports.Set("setPluginRSP", Napi::Function::New(env, m64b_interface::WrapSetPluginRSP));
    
    // Functions
    exports.Set("runEmulator", Napi::Function::New(env, m64b_interface::WrapRunEmulator));
    exports.Set("runEmulatorAsync", Napi::Function::New(env, m64b_interface::WrapRunEmulatorAsync));
    exports.Set("pauseEmulator", Napi::Function::New(env, m64b_interface::WrapPauseEmulator));
    exports.Set("resumeEmulator", Napi::Function::New(env, m64b_interface::WrapResumeEmulator));
    exports.Set("stopEmulator", Napi::Function::New(env, m64b_interface::WrapStopEmulator));

    return exports;
}