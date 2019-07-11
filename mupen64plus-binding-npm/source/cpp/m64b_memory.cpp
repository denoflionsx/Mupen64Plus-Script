#include <m64p_binding_memory.h>
#include "m64b_memory.h"

// #########################################################
// ## RDRam Memory
// #########################################################

Napi::Number m64b_memory::WrapRdRamRead64(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();

    uint32 addr = info[0].As<Napi::Number>().Uint32Value();
    uint64 value = rdramRead64(addr);

    return Napi::Number::New(env, value);
}

Napi::Number m64b_memory::WrapRdRamReadU64(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();

    uint32 addr = info[0].As<Napi::Number>().Uint32Value();
    uint64 value = rdramReadU64(addr);
    
    return Napi::Number::New(env, value);
}

Napi::Number m64b_memory::WrapRdRamWrite64(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();

    uint32 addr = info[0].As<Napi::Number>().Uint32Value();
    uint64 value = info[1].As<Napi::Number>().Int64Value();
    rdramWrite64(addr, value);
    
    return Napi::Number::New(env, 0);
}

Napi::Number m64b_memory::WrapRdRamWriteU64(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();

    uint32 addr = info[0].As<Napi::Number>().Uint32Value();
    uint64 value = info[1].As<Napi::Number>().Int64Value();
    rdramWriteU64(addr, value);
    
    return Napi::Number::New(env, 0);
}

Napi::Number m64b_memory::WrapRdRamRead32(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();

    uint32 addr = info[0].As<Napi::Number>().Uint32Value();
    uint32 value = rdramRead32(addr);
    
    return Napi::Number::New(env, value);
}

Napi::Number m64b_memory::WrapRdRamReadU32(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();

    uint32 addr = info[0].As<Napi::Number>().Uint32Value();
    uint32 value = rdramReadU32(addr);
    
    return Napi::Number::New(env, value);
}

Napi::Number m64b_memory::WrapRdRamWrite32(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();

    uint32 addr = info[0].As<Napi::Number>().Uint32Value();
    uint32 value = info[1].As<Napi::Number>().Uint32Value();
    rdramWrite32(addr, value);
    
    return Napi::Number::New(env, 0);
}

Napi::Number m64b_memory::WrapRdRamWriteU32(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();

    uint32 addr = info[0].As<Napi::Number>().Uint32Value();
    uint32 value = info[1].As<Napi::Number>().Uint32Value();
    rdramWriteU32(addr, value);
    
    return Napi::Number::New(env, 0);
}

Napi::Number m64b_memory::WrapRdRamRead16(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();

    uint32 addr = info[0].As<Napi::Number>().Uint32Value();
    uint16 value = rdramRead16(addr);
    
    return Napi::Number::New(env, value);
}

Napi::Number m64b_memory::WrapRdRamWrite16(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();

    uint32 addr = info[0].As<Napi::Number>().Uint32Value();
    uint16 value = info[1].As<Napi::Number>().Uint32Value();
    rdramWrite16(addr, value);
    
    return Napi::Number::New(env, 0);
}

Napi::Number m64b_memory::WrapRdRamRead8(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();

    uint32 addr = info[0].As<Napi::Number>().Uint32Value();
    uint8 value = rdramRead8(addr);
    
    return Napi::Number::New(env, value);
}

Napi::Number m64b_memory::WrapRdRamWrite8(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();

    uint32 addr = info[0].As<Napi::Number>().Uint32Value();
    uint8 value = info[1].As<Napi::Number>().Uint32Value();
    rdramWrite8(addr, value);
    
    return Napi::Number::New(env, 0);
}

// #########################################################
// ## Rom Memory
// #########################################################

Napi::Number m64b_memory::WrapRomRead64(const Napi::CallbackInfo& info) {
	Napi::Env env = info.Env();

	uint32 addr = info[0].As<Napi::Number>().Uint32Value();
	uint64 value = romRead64(addr);

	return Napi::Number::New(env, value);
}

Napi::Number m64b_memory::WrapRomReadU64(const Napi::CallbackInfo& info) {
	Napi::Env env = info.Env();

	uint32 addr = info[0].As<Napi::Number>().Uint32Value();
	uint64 value = romReadU64(addr);

	return Napi::Number::New(env, value);
}

Napi::Number m64b_memory::WrapRomWrite64(const Napi::CallbackInfo& info) {
	Napi::Env env = info.Env();

	uint32 addr = info[0].As<Napi::Number>().Uint32Value();
	uint64 value = info[1].As<Napi::Number>().Int64Value();
	romWrite64(addr, value);

	return Napi::Number::New(env, 0);
}

Napi::Number m64b_memory::WrapRomWriteU64(const Napi::CallbackInfo& info) {
	Napi::Env env = info.Env();

	uint32 addr = info[0].As<Napi::Number>().Uint32Value();
	uint64 value = info[1].As<Napi::Number>().Int64Value();
	romWriteU64(addr, value);

	return Napi::Number::New(env, 0);
}

Napi::Number m64b_memory::WrapRomRead32(const Napi::CallbackInfo& info) {
	Napi::Env env = info.Env();

	uint32 addr = info[0].As<Napi::Number>().Uint32Value();
	uint32 value = romRead32(addr);

	return Napi::Number::New(env, value);
}

Napi::Number m64b_memory::WrapRomReadU32(const Napi::CallbackInfo& info) {
	Napi::Env env = info.Env();

	uint32 addr = info[0].As<Napi::Number>().Uint32Value();
	uint32 value = romReadU32(addr);

	return Napi::Number::New(env, value);
}

Napi::Number m64b_memory::WrapRomWrite32(const Napi::CallbackInfo& info) {
	Napi::Env env = info.Env();

	uint32 addr = info[0].As<Napi::Number>().Uint32Value();
	uint32 value = info[1].As<Napi::Number>().Uint32Value();
	romWrite32(addr, value);

	return Napi::Number::New(env, 0);
}

Napi::Number m64b_memory::WrapRomWriteU32(const Napi::CallbackInfo& info) {
	Napi::Env env = info.Env();

	uint32 addr = info[0].As<Napi::Number>().Uint32Value();
	uint32 value = info[1].As<Napi::Number>().Uint32Value();
	romWriteU32(addr, value);

	return Napi::Number::New(env, 0);
}

Napi::Number m64b_memory::WrapRomRead16(const Napi::CallbackInfo& info) {
	Napi::Env env = info.Env();

	uint32 addr = info[0].As<Napi::Number>().Uint32Value();
	uint16 value = romRead16(addr);

	return Napi::Number::New(env, value);
}

Napi::Number m64b_memory::WrapRomWrite16(const Napi::CallbackInfo& info) {
	Napi::Env env = info.Env();

	uint32 addr = info[0].As<Napi::Number>().Uint32Value();
	uint16 value = info[1].As<Napi::Number>().Uint32Value();
	romWrite16(addr, value);

	return Napi::Number::New(env, 0);
}

Napi::Number m64b_memory::WrapRomRead8(const Napi::CallbackInfo& info) {
	Napi::Env env = info.Env();

	uint32 addr = info[0].As<Napi::Number>().Uint32Value();
	uint8 value = romRead8(addr);

	return Napi::Number::New(env, value);
}

Napi::Number m64b_memory::WrapRomWrite8(const Napi::CallbackInfo& info) {
	Napi::Env env = info.Env();

	uint32 addr = info[0].As<Napi::Number>().Uint32Value();
	uint8 value = info[1].As<Napi::Number>().Uint32Value();
	romWrite8(addr, value);

	return Napi::Number::New(env, 0);
}

// #########################################################
// ## NAPI Export
// #########################################################

Napi::Object m64b_memory::Init(Napi::Env env, Napi::Object exports) {

    // RDRam Memory
    exports.Set("rdramRead64", Napi::Function::New(env, m64b_memory::WrapRdRamRead64));
    exports.Set("rdramReadU64", Napi::Function::New(env, m64b_memory::WrapRdRamReadU64));
    exports.Set("rdramWrite64", Napi::Function::New(env, m64b_memory::WrapRdRamWrite64));
    exports.Set("rdramWriteU64", Napi::Function::New(env, m64b_memory::WrapRdRamWriteU64));
    exports.Set("rdramRead32", Napi::Function::New(env, m64b_memory::WrapRdRamRead32));
    exports.Set("rdramReadU32", Napi::Function::New(env, m64b_memory::WrapRdRamReadU32));
    exports.Set("rdramWrite32", Napi::Function::New(env, m64b_memory::WrapRdRamWrite32));
    exports.Set("rdramWriteU32", Napi::Function::New(env, m64b_memory::WrapRdRamWriteU32));
    exports.Set("rdramRead16", Napi::Function::New(env, m64b_memory::WrapRdRamRead16));
    exports.Set("rdramWrite16", Napi::Function::New(env, m64b_memory::WrapRdRamWrite16));
    exports.Set("rdramRead8", Napi::Function::New(env, m64b_memory::WrapRdRamRead8));
    exports.Set("rdramWrite8", Napi::Function::New(env, m64b_memory::WrapRdRamWrite8));
    
    // Rom Memory
    exports.Set("romRead64", Napi::Function::New(env, m64b_memory::WrapRomRead64));
    exports.Set("romReadU64", Napi::Function::New(env, m64b_memory::WrapRomReadU64));
    exports.Set("romWrite64", Napi::Function::New(env, m64b_memory::WrapRomWrite64));
    exports.Set("romWriteU64", Napi::Function::New(env, m64b_memory::WrapRomWriteU64));
    exports.Set("romRead32", Napi::Function::New(env, m64b_memory::WrapRomRead32));
    exports.Set("romReadU32", Napi::Function::New(env, m64b_memory::WrapRomReadU32));
    exports.Set("romWrite32", Napi::Function::New(env, m64b_memory::WrapRomWrite32));
    exports.Set("romWriteU32", Napi::Function::New(env, m64b_memory::WrapRomWriteU32));
    exports.Set("romRead16", Napi::Function::New(env, m64b_memory::WrapRomRead16));
    exports.Set("romWrite16", Napi::Function::New(env, m64b_memory::WrapRomWrite16));
    exports.Set("romRead8", Napi::Function::New(env, m64b_memory::WrapRomRead8));
    exports.Set("romWrite8", Napi::Function::New(env, m64b_memory::WrapRomWrite8));

    return exports;
}