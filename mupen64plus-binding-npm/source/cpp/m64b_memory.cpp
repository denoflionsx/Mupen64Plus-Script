#include "m64b_memory.h"
#include <m64p_binding_memory.h>

// #########################################################
// ## RDRam Memory
// #########################################################

Uint8Array npmRdRamReadBuffer(const CallbackInfo& info) {
    uint32 addr = info[0].As<Number>().Uint32Value();
    size_t len = info[1].As<Number>().Uint32Value();

    const char* mem = rdramReadBuffer(addr, len);
    Uint8Array arr = Uint8Array::New(info.Env(), len);
    
    for (size_t i = 0; i < len; i++) 
        arr.Set(i, mem[i]);

    return arr;
}

Number npmRdRamRead64(const CallbackInfo& info) {
    uint32 addr = info[0].As<Number>().Uint32Value();
    uint64 value = rdramRead64(addr);
    return Number::New(info.Env(), value);
}

Number npmRdRamReadU64(const CallbackInfo& info) {
    uint32 addr = info[0].As<Number>().Uint32Value();
    uint64 value = rdramReadU64(addr);    
    return Number::New(info.Env(), value);
}

Number npmRdRamRead32(const CallbackInfo& info) {
    uint32 addr = info[0].As<Number>().Uint32Value();
    uint32 value = rdramRead32(addr);    
    return Number::New(info.Env(), value);
}

Number npmRdRamReadU32(const CallbackInfo& info) {
    uint32 addr = info[0].As<Number>().Uint32Value();
    uint32 value = rdramReadU32(addr);    
    return Number::New(info.Env(), value);
}

Number npmRdRamRead16(const CallbackInfo& info) {
    uint32 addr = info[0].As<Number>().Uint32Value();
    uint16 value = rdramRead16(addr);    
    return Number::New(info.Env(), value);
}

Number npmRdRamRead8(const CallbackInfo& info) {
    uint32 addr = info[0].As<Number>().Uint32Value();
    uint8 value = rdramRead8(addr);    
    return Number::New(info.Env(), value);
}

// -------------------------------------------

Value npmRdRamWriteBuffer(const CallbackInfo& info) {
    uint32 addr = info[0].As<Number>().Uint32Value();
    Uint8Array arr = info[1].As<Uint8Array>();
    size_t len = arr.ByteLength(); uint8 val;

    for (size_t i = 0; i < len; i++) {
        val = arr.Get(i).As<Number>().Uint32Value();
        rdramWrite8(addr + i, val);
    }
    
    return info.Env().Undefined();
}

Value npmRdRamWrite64(const CallbackInfo& info) {
    uint32 addr = info[0].As<Number>().Uint32Value();
    uint64 value = info[1].As<Number>().Int64Value();
    rdramWrite64(addr, value);    
    return info.Env().Undefined();
}

Value npmRdRamWriteU64(const CallbackInfo& info) {
    uint32 addr = info[0].As<Number>().Uint32Value();
    uint64 value = info[1].As<Number>().Int64Value();
    rdramWriteU64(addr, value);    
    return info.Env().Undefined();
}

Value npmRdRamWrite32(const CallbackInfo& info) {
    uint32 addr = info[0].As<Number>().Uint32Value();
    uint32 value = info[1].As<Number>().Uint32Value();
    rdramWrite32(addr, value);    
    return info.Env().Undefined();
}

Value npmRdRamWriteU32(const CallbackInfo& info) {
    uint32 addr = info[0].As<Number>().Uint32Value();
    uint32 value = info[1].As<Number>().Uint32Value();
    rdramWriteU32(addr, value);    
    return info.Env().Undefined();
}

Value npmRdRamWrite16(const CallbackInfo& info) {
    uint32 addr = info[0].As<Number>().Uint32Value();
    uint16 value = info[1].As<Number>().Uint32Value();
    rdramWrite16(addr, value);    
    return info.Env().Undefined();
}

Value npmRdRamWrite8(const CallbackInfo& info) {
    uint32 addr = info[0].As<Number>().Uint32Value();
    uint8 value = info[1].As<Number>().Uint32Value();
    rdramWrite8(addr, value);    
    return info.Env().Undefined();
}

// #########################################################
// ## Rom Memory
// #########################################################

Uint8Array npmRomReadBuffer(const CallbackInfo& info) {
    uint32 addr = info[0].As<Number>().Uint32Value();
    size_t len = info[1].As<Number>().Uint32Value();

    const char* mem = romReadBuffer(addr, len);
    Uint8Array arr = Uint8Array::New(info.Env(), len);
    
    for (size_t i = 0; i < len; i++) 
        arr.Set(i, mem[i]);

    return arr;
}

Number npmRomRead64(const CallbackInfo& info) {
	uint32 addr = info[0].As<Number>().Uint32Value();
	uint64 value = romRead64(addr);
	return Number::New(info.Env(), value);
}

Number npmRomRead32(const CallbackInfo& info) {
	uint32 addr = info[0].As<Number>().Uint32Value();
	uint32 value = romRead32(addr);
	return Number::New(info.Env(), value);
}

Number npmRomRead16(const CallbackInfo& info) {
	uint32 addr = info[0].As<Number>().Uint32Value();
	uint16 value = romRead16(addr);
	return Number::New(info.Env(), value);
}

Number npmRomRead8(const CallbackInfo& info) {
	uint32 addr = info[0].As<Number>().Uint32Value();
	uint8 value = romRead8(addr);
	return Number::New(info.Env(), value);
}

// -------------------------------------------

Value npmRomWriteBuffer(const CallbackInfo& info) {
    uint32 addr = info[0].As<Number>().Uint32Value();
    Uint8Array arr = info[1].As<Uint8Array>();
    size_t len = arr.ByteLength(); uint8 val;

    for (size_t i = 0; i < len; i++) {
        val = arr.Get(i).As<Number>().Uint32Value();
        romWrite8(addr + i, val);
    }
    
    return info.Env().Undefined();
}

Value npmRomWrite64(const CallbackInfo& info) {
	uint32 addr = info[0].As<Number>().Uint32Value();
	uint64 value = info[1].As<Number>().Int64Value();
	romWrite64(addr, value);
    return info.Env().Undefined();
}

Value npmRomWrite32(const CallbackInfo& info) {
	uint32 addr = info[0].As<Number>().Uint32Value();
	uint32 value = info[1].As<Number>().Uint32Value();
	romWrite32(addr, value);
    return info.Env().Undefined();
}

Value npmRomWrite16(const CallbackInfo& info) {
	uint32 addr = info[0].As<Number>().Uint32Value();
	uint16 value = info[1].As<Number>().Uint32Value();
	romWrite16(addr, value);
    return info.Env().Undefined();
}

Value npmRomWrite8(const CallbackInfo& info) {
	uint32 addr = info[0].As<Number>().Uint32Value();
	uint8 value = info[1].As<Number>().Uint32Value();
	romWrite8(addr, value);

    return info.Env().Undefined();
}

// #########################################################
// ## SaveStates
// #########################################################

Value npmSaveStatesRefreshHack(const CallbackInfo& info) {
	savestatesRefreshHack();
    return info.Env().Undefined();
}

// #########################################################
// ## NAPI Export
// #########################################################

Object M64B_Memory_Init(Env env, Object exports) {

    // RDRam Memory
    exports.Set("rdramReadBuffer", Function::New(env, npmRdRamReadBuffer));
    exports.Set("rdramRead64", Function::New(env, npmRdRamRead64));
    exports.Set("rdramReadU64", Function::New(env, npmRdRamReadU64));
    exports.Set("rdramRead32", Function::New(env, npmRdRamRead32));
    exports.Set("rdramReadU32", Function::New(env, npmRdRamReadU32));
    exports.Set("rdramRead16", Function::New(env, npmRdRamRead16));
    exports.Set("rdramRead8", Function::New(env, npmRdRamRead8));

    exports.Set("rdramWriteBuffer", Function::New(env, npmRdRamWriteBuffer));
    exports.Set("rdramWrite64", Function::New(env, npmRdRamWrite64));
    exports.Set("rdramWriteU64", Function::New(env, npmRdRamWriteU64));
    exports.Set("rdramWrite32", Function::New(env, npmRdRamWrite32));
    exports.Set("rdramWriteU32", Function::New(env, npmRdRamWriteU32));
    exports.Set("rdramWrite16", Function::New(env, npmRdRamWrite16));
    exports.Set("rdramWrite8", Function::New(env, npmRdRamWrite8));
    
    // Rom Memory
    exports.Set("romReadBuffer", Function::New(env, npmRomReadBuffer));
    exports.Set("romRead64", Function::New(env, npmRomRead64));
    exports.Set("romRead32", Function::New(env, npmRomRead32));
    exports.Set("romRead16", Function::New(env, npmRomRead16));
    exports.Set("romRead8", Function::New(env, npmRomRead8));

    exports.Set("romWriteBuffer", Function::New(env, npmRomWriteBuffer));
    exports.Set("romWrite64", Function::New(env, npmRomWrite64));
    exports.Set("romWrite32", Function::New(env, npmRomWrite32));
    exports.Set("romWrite16", Function::New(env, npmRomWrite16));
    exports.Set("romWrite8", Function::New(env, npmRomWrite8));

    // SaveStates
    exports.Set("savestatesRefreshHack", Function::New(env, npmSaveStatesRefreshHack));

    return exports;
}