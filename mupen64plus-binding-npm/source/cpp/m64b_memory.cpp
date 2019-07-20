#include "m64b_memory.h"
#include <m64p_binding_memory.h>

// #########################################################
// ## RDRam Memory
// #########################################################

Buffer<uint8_t> npmRdRamReadBuffer(const CallbackInfo& info) {
    uint32_t addr = info[0].As<Number>().Uint32Value();
    size_t len = info[1].As<Number>().Uint32Value();

    const uint8_t* mem = rdramReadBuffer(addr, len);
    Buffer<uint8_t> arr = Buffer<uint8_t>::New(info.Env(), len);
    
    for (size_t i = 0; i < len; i++) 
        arr.Set(i, mem[i]);

    return arr;
}

Number npmRdRamRead32(const CallbackInfo& info) {
    uint32_t addr = info[0].As<Number>().Uint32Value();
    uint32_t value = rdramRead32(addr);    
    return Number::New(info.Env(), value);
}

Number npmRdRamRead16(const CallbackInfo& info) {
    uint32_t addr = info[0].As<Number>().Uint32Value();
    uint16_t value = rdramRead16(addr);    
    return Number::New(info.Env(), value);
}

Number npmRdRamRead8(const CallbackInfo& info) {
    uint32_t addr = info[0].As<Number>().Uint32Value();
    uint8_t value = rdramRead8(addr);    
    return Number::New(info.Env(), value);
}

// -------------------------------------------

Value npmRdRamWriteBuffer(const CallbackInfo& info) {
    uint32_t addr = info[0].As<Number>().Uint32Value();
    Uint8Array arr = info[1].As<Uint8Array>();
    size_t len = arr.ByteLength(); uint8_t val;

    for (size_t i = 0; i < len; i++) {
        val = arr.Get(i).As<Number>().Uint32Value();
        rdramWrite8(addr + i, val);
    }
    
    return info.Env().Undefined();
}

Value npmRdRamWrite32(const CallbackInfo& info) {
    uint32_t addr = info[0].As<Number>().Uint32Value();
    uint32_t value = info[1].As<Number>().Uint32Value();
    rdramWrite32(addr, value);    
    return info.Env().Undefined();
}

Value npmRdRamWrite16(const CallbackInfo& info) {
    uint32_t addr = info[0].As<Number>().Uint32Value();
    uint16_t value = info[1].As<Number>().Uint32Value();
    rdramWrite16(addr, value);    
    return info.Env().Undefined();
}

Value npmRdRamWrite8(const CallbackInfo& info) {
    uint32_t addr = info[0].As<Number>().Uint32Value();
    uint8_t value = info[1].As<Number>().Uint32Value();
    rdramWrite8(addr, value);    
    return info.Env().Undefined();
}

// #########################################################
// ## Rom Memory
// #########################################################

Buffer<uint8_t> npmRomReadBuffer(const CallbackInfo& info) {
    uint32_t addr = info[0].As<Number>().Uint32Value();
    size_t len = info[1].As<Number>().Uint32Value();

    const uint8_t* mem = romReadBuffer(addr, len);
    Buffer<uint8_t> arr = Buffer<uint8_t>::New(info.Env(), len);
    
    for (size_t i = 0; i < len; i++) 
        arr.Set(i, mem[i]);

    return arr;
}

Number npmRomRead32(const CallbackInfo& info) {
	uint32_t addr = info[0].As<Number>().Uint32Value();
	uint32_t value = romRead32(addr);
	return Number::New(info.Env(), value);
}

Number npmRomRead16(const CallbackInfo& info) {
	uint32_t addr = info[0].As<Number>().Uint32Value();
	uint16_t value = romRead16(addr);
	return Number::New(info.Env(), value);
}

Number npmRomRead8(const CallbackInfo& info) {
	uint32_t addr = info[0].As<Number>().Uint32Value();
	uint8_t value = romRead8(addr);
	return Number::New(info.Env(), value);
}

// -------------------------------------------

Value npmRomWriteBuffer(const CallbackInfo& info) {
    uint32_t addr = info[0].As<Number>().Uint32Value();
    Uint8Array arr = info[1].As<Uint8Array>();
    size_t len = arr.ByteLength(); uint8_t val;

    for (size_t i = 0; i < len; i++) {
        val = arr.Get(i).As<Number>().Uint32Value();
        romWrite8(addr + i, val);
    }
    
    return info.Env().Undefined();
}

Value npmRomWrite32(const CallbackInfo& info) {
	uint32_t addr = info[0].As<Number>().Uint32Value();
	uint32_t value = info[1].As<Number>().Uint32Value();
	romWrite32(addr, value);
    return info.Env().Undefined();
}

Value npmRomWrite16(const CallbackInfo& info) {
	uint32_t addr = info[0].As<Number>().Uint32Value();
	uint16_t value = info[1].As<Number>().Uint32Value();
	romWrite16(addr, value);
    return info.Env().Undefined();
}

Value npmRomWrite8(const CallbackInfo& info) {
	uint32_t addr = info[0].As<Number>().Uint32Value();
	uint8_t value = info[1].As<Number>().Uint32Value();
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
    exports.Set("rdramRead32", Function::New(env, npmRdRamRead32));
    exports.Set("rdramRead16", Function::New(env, npmRdRamRead16));
    exports.Set("rdramRead8", Function::New(env, npmRdRamRead8));

    exports.Set("rdramWriteBuffer", Function::New(env, npmRdRamWriteBuffer));
    exports.Set("rdramWrite32", Function::New(env, npmRdRamWrite32));
    exports.Set("rdramWrite16", Function::New(env, npmRdRamWrite16));
    exports.Set("rdramWrite8", Function::New(env, npmRdRamWrite8));
    
    // Rom Memory
    exports.Set("romReadBuffer", Function::New(env, npmRomReadBuffer));
    exports.Set("romRead32", Function::New(env, npmRomRead32));
    exports.Set("romRead16", Function::New(env, npmRomRead16));
    exports.Set("romRead8", Function::New(env, npmRomRead8));

    exports.Set("romWriteBuffer", Function::New(env, npmRomWriteBuffer));
    exports.Set("romWrite32", Function::New(env, npmRomWrite32));
    exports.Set("romWrite16", Function::New(env, npmRomWrite16));
    exports.Set("romWrite8", Function::New(env, npmRomWrite8));

    // SaveStates
    exports.Set("savestatesRefreshHack", Function::New(env, npmSaveStatesRefreshHack));

    return exports;
}