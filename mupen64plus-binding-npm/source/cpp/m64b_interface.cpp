#include <napi.h>
#include <m64p_binding_interface.h>
#include <m64p_binding_memory.h>

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

Napi::Number WrapRunEmulatorAsync(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();

    std::string input = info[0].As<Napi::String>().Utf8Value();
    int ret = RunEmulatorAsync(input.c_str());

    return Napi::Number::New(env, ret);
}

// #########################################################
// ## RD Memory
// #########################################################

Napi::Number WrapMemRead64(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();

    uint32 addr = info[0].As<Napi::Number>().Uint32Value();
    uint64 value = MemRead64(addr);
    
    return Napi::Number::New(env, value);
}

Napi::Number WrapMemReadU64(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();

    uint32 addr = info[0].As<Napi::Number>().Uint32Value();
    uint64 value = MemReadU64(addr);
    
    return Napi::Number::New(env, value);
}

Napi::Number WrapMemWrite64(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();

    uint32 addr = info[0].As<Napi::Number>().Uint32Value();
    uint64 value = info[1].As<Napi::Number>().Int64Value();
    MemWrite64(addr, value);
    
    return Napi::Number::New(env, 0);
}

Napi::Number WrapMemWriteU64(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();

    uint32 addr = info[0].As<Napi::Number>().Uint32Value();
    uint64 value = info[1].As<Napi::Number>().Int64Value();
    MemWriteU64(addr, value);
    
    return Napi::Number::New(env, 0);
}

Napi::Number WrapMemRead32(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();

    uint32 addr = info[0].As<Napi::Number>().Uint32Value();
    uint32 value = MemRead32(addr);
    
    return Napi::Number::New(env, value);
}

Napi::Number WrapMemReadU32(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();

    uint32 addr = info[0].As<Napi::Number>().Uint32Value();
    uint32 value = MemReadU32(addr);
    
    return Napi::Number::New(env, value);
}

Napi::Number WrapMemWrite32(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();

    uint32 addr = info[0].As<Napi::Number>().Uint32Value();
    uint32 value = info[1].As<Napi::Number>().Uint32Value();
    MemWrite32(addr, value);
    
    return Napi::Number::New(env, 0);
}

Napi::Number WrapMemWriteU32(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();

    uint32 addr = info[0].As<Napi::Number>().Uint32Value();
    uint32 value = info[1].As<Napi::Number>().Uint32Value();
    MemWriteU32(addr, value);
    
    return Napi::Number::New(env, 0);
}

Napi::Number WrapMemRead16(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();

    uint32 addr = info[0].As<Napi::Number>().Uint32Value();
    uint16 value = MemRead16(addr);
    
    return Napi::Number::New(env, value);
}

Napi::Number WrapMemWrite16(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();

    uint32 addr = info[0].As<Napi::Number>().Uint32Value();
    uint16 value = info[1].As<Napi::Number>().Uint32Value();
    MemWrite16(addr, value);
    
    return Napi::Number::New(env, 0);
}

Napi::Number WrapMemRead8(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();

    uint32 addr = info[0].As<Napi::Number>().Uint32Value();
    uint8 value = MemRead8(addr);
    
    return Napi::Number::New(env, value);
}

Napi::Number WrapMemWrite8(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();

    uint32 addr = info[0].As<Napi::Number>().Uint32Value();
    uint8 value = info[1].As<Napi::Number>().Uint32Value();
    MemWrite8(addr, value);
    
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
    exports.Set("runEmulatorAsync", Napi::Function::New(env, WrapRunEmulatorAsync));

    //RD Memory
    exports.Set("memRead64", Napi::Function::New(env, WrapMemRead64));
    exports.Set("memReadU64", Napi::Function::New(env, WrapMemReadU64));
    exports.Set("memWrite64", Napi::Function::New(env, WrapMemWrite64));
    exports.Set("memWriteU64", Napi::Function::New(env, WrapMemWriteU64));
    exports.Set("memRead32", Napi::Function::New(env, WrapMemRead32));
    exports.Set("memReadU32", Napi::Function::New(env, WrapMemReadU32));
    exports.Set("memWrite32", Napi::Function::New(env, WrapMemWrite32));
    exports.Set("memWriteU32", Napi::Function::New(env, WrapMemWriteU32));
    exports.Set("memRead16", Napi::Function::New(env, WrapMemRead16));
    exports.Set("memWrite16", Napi::Function::New(env, WrapMemWrite16));
    exports.Set("memRead8", Napi::Function::New(env, WrapMemRead8));
    exports.Set("memWrite8", Napi::Function::New(env, WrapMemWrite8));

    return exports;
}

NODE_API_MODULE(NODE_GYP_MODULE_NAME, Init)