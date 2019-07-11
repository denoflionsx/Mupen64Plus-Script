#include <napi.h>

namespace m64b_memory 
{

    // #########################################################
    // ## RDRam Memory
    // #########################################################

    Napi::Number WrapRdRamRead64(const Napi::CallbackInfo& info);
    Napi::Number WrapRdRamReadU64(const Napi::CallbackInfo& info);
    Napi::Number WrapRdRamWrite64(const Napi::CallbackInfo& info);
    Napi::Number WrapRdRamWriteU64(const Napi::CallbackInfo& info);
    Napi::Number WrapRdRamRead32(const Napi::CallbackInfo& info);
    Napi::Number WrapRdRamReadU32(const Napi::CallbackInfo& info);
    Napi::Number WrapRdRamWrite32(const Napi::CallbackInfo& info);
    Napi::Number WrapRdRamWriteU32(const Napi::CallbackInfo& info);
    Napi::Number WrapRdRamRead16(const Napi::CallbackInfo& info);
    Napi::Number WrapRdRamWrite16(const Napi::CallbackInfo& info);
    Napi::Number WrapRdRamRead8(const Napi::CallbackInfo& info);
    Napi::Number WrapRdRamWrite8(const Napi::CallbackInfo& info);

    // #########################################################
    // ## Rom Memory
    // #########################################################

    Napi::Number WrapRomRead64(const Napi::CallbackInfo& info);
    Napi::Number WrapRomReadU64(const Napi::CallbackInfo& info);
    Napi::Number WrapRomWrite64(const Napi::CallbackInfo& info);
    Napi::Number WrapRomWriteU64(const Napi::CallbackInfo& info);
    Napi::Number WrapRomRead32(const Napi::CallbackInfo& info);
    Napi::Number WrapRomReadU32(const Napi::CallbackInfo& info);
    Napi::Number WrapRomWrite32(const Napi::CallbackInfo& info);
    Napi::Number WrapRomWriteU32(const Napi::CallbackInfo& info);
    Napi::Number WrapRomRead16(const Napi::CallbackInfo& info);
    Napi::Number WrapRomWrite16(const Napi::CallbackInfo& info);
    Napi::Number WrapRomRead8(const Napi::CallbackInfo& info);
    Napi::Number WrapRomWrite8(const Napi::CallbackInfo& info);

    // #########################################################
    // ## NAPI Export
    // #########################################################

    Napi::Object Init(Napi::Env env, Napi::Object exports);

}