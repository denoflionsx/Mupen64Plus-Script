#include <napi.h>
#include <API/m64b.h>

Napi::Number WrapSetCoreLib(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();

    std::string input = info[0].As<Napi::String>().Utf8Value();
    SetCoreLib(input.c_str());

    return Napi::Number::New(env, 0);
}

// #########################################################
// ## Paths
// #########################################################

Napi::Number WrapSetConfigDir(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();

    std::string input = info[0].As<Napi::String>().Utf8Value();
    SetConfigDir(input.c_str());

    return Napi::Number::New(env, 0);
}

Napi::Number WrapSetDataDir(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();

    std::string input = info[0].As<Napi::String>().Utf8Value();
    SetDataDir(input.c_str());

    return Napi::Number::New(env, 0);
}

Napi::Number WrapSetPluginDir(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();

    std::string input = info[0].As<Napi::String>().Utf8Value();
    SetPluginDir(input.c_str());

    return Napi::Number::New(env, 0);
}

Napi::Number WrapSetPluginAudio(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();

    std::string input = info[0].As<Napi::String>().Utf8Value();
    SetPluginAudio(input.c_str());

    return Napi::Number::New(env, 0);
}

Napi::Number WrapSetPluginGFX(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();

    std::string input = info[0].As<Napi::String>().Utf8Value();
    SetPluginGFX(input.c_str());

    return Napi::Number::New(env, 0);
}

Napi::Number WrapSetPluginInput(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();

    std::string input = info[0].As<Napi::String>().Utf8Value();
    SetPluginInput(input.c_str());

    return Napi::Number::New(env, 0);
}

Napi::Number WrapSetPluginRSP(const Napi::CallbackInfo& info) {
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

Napi::Number WrapRunEmulator(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();

    std::string input = info[0].As<Napi::String>().Utf8Value();
    int ret = RunEmulator(input.c_str());

    return Napi::Number::New(env, ret);
}

// #########################################################
// ## RD Memory
// #########################################################

Napi::Number WrapRdMemRead64(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();

    uint32 addr = info[0].As<Napi::Number>().Uint32Value();
    uint64 value = RdMemRead64(addr);
    
    return Napi::Number::New(env, value);
}

Napi::Number WrapRdMemReadU64(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();

    uint32 addr = info[0].As<Napi::Number>().Uint32Value();
    uint64 value = RdMemReadU64(addr);
    
    return Napi::Number::New(env, value);
}

Napi::Number WrapRdMemWrite64(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();

    uint32 addr = info[0].As<Napi::Number>().Uint32Value();
    uint64 value = info[1].As<Napi::Number>().Int64Value();
    RdMemWrite64(addr, value);
    
    return Napi::Number::New(env, 0);
}

Napi::Number WrapRdMemWriteU64(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();

    uint32 addr = info[0].As<Napi::Number>().Uint32Value();
    uint64 value = info[1].As<Napi::Number>().Int64Value();
    RdMemWriteU64(addr, value);
    
    return Napi::Number::New(env, 0);
}

Napi::Number WrapRdMemRead32(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();

    uint32 addr = info[0].As<Napi::Number>().Uint32Value();
    uint32 value = RdMemRead32(addr);
    
    return Napi::Number::New(env, value);
}

Napi::Number WrapRdMemReadU32(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();

    uint32 addr = info[0].As<Napi::Number>().Uint32Value();
    uint32 value = RdMemReadU32(addr);
    
    return Napi::Number::New(env, value);
}

Napi::Number WrapRdMemWrite32(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();

    uint32 addr = info[0].As<Napi::Number>().Uint32Value();
    uint32 value = info[1].As<Napi::Number>().Uint32Value();
    RdMemWrite32(addr, value);
    
    return Napi::Number::New(env, 0);
}

Napi::Number WrapRdMemWriteU32(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();

    uint32 addr = info[0].As<Napi::Number>().Uint32Value();
    uint32 value = info[1].As<Napi::Number>().Uint32Value();
    RdMemWriteU32(addr, value);
    
    return Napi::Number::New(env, 0);
}

Napi::Number WrapRdMemRead16(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();

    uint32 addr = info[0].As<Napi::Number>().Uint32Value();
    uint16 value = RdMemRead16(addr);
    
    return Napi::Number::New(env, value);
}

Napi::Number WrapRdMemWrite16(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();

    uint32 addr = info[0].As<Napi::Number>().Uint32Value();
    uint16 value = info[1].As<Napi::Number>().Uint32Value();
    RdMemWrite16(addr, value);
    
    return Napi::Number::New(env, 0);
}

Napi::Number WrapRdMemRead8(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();

    uint32 addr = info[0].As<Napi::Number>().Uint32Value();
    uint8 value = RdMemRead8(addr);
    
    return Napi::Number::New(env, value);
}

Napi::Number WrapRdMemWrite8(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();

    uint32 addr = info[0].As<Napi::Number>().Uint32Value();
    uint8 value = info[1].As<Napi::Number>().Uint32Value();
    RdMemWrite8(addr, value);
    
    return Napi::Number::New(env, 0);
}

// #########################################################
// ## NAPI Export
// #########################################################

Napi::Object Init(Napi::Env env, Napi::Object exports) {
    // Paths
    exports.Set("setCoreLib", Napi::Function::New(env, WrapSetCoreLib));
    exports.Set("setConfigDir", Napi::Function::New(env, WrapSetConfigDir));
    exports.Set("setDataDir", Napi::Function::New(env, WrapSetDataDir));    
    exports.Set("setPluginDir", Napi::Function::New(env, WrapSetPluginDir));
    exports.Set("setPluginAudio", Napi::Function::New(env, WrapSetPluginAudio));
    exports.Set("setPluginGFX", Napi::Function::New(env, WrapSetPluginGFX));
    exports.Set("setPluginInput", Napi::Function::New(env, WrapSetPluginInput));
    exports.Set("setPluginRSP", Napi::Function::New(env, WrapSetPluginRSP));
    
    // Functions
    exports.Set("runEmulator", Napi::Function::New(env, WrapRunEmulator));

    //RD Memory
    exports.Set("rdmemRead64", Napi::Function::New(env, WrapRdMemRead64));

    return exports;
}

NODE_API_MODULE(NODE_GYP_MODULE_NAME, Init)