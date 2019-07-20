#ifndef _M64B_MEMORY_
#define _M64B_MEMORY_

#include <napi.h>
using namespace Napi;

// #########################################################
// ## RDRam Memory
// #########################################################

Buffer<uint8_t> npmRdRamReadBuffer(const CallbackInfo& info);
Number npmRdRamRead32(const CallbackInfo& info);
Number npmRdRamRead16(const CallbackInfo& info);
Number npmRdRamRead8(const CallbackInfo& info);

Value npmRdRamWriteBuffer(const CallbackInfo& info);
Value npmRdRamWrite32(const CallbackInfo& info);
Value npmRdRamWrite16(const CallbackInfo& info);
Value npmRdRamWrite8(const CallbackInfo& info);

// #########################################################
// ## Rom Memory
// #########################################################

Buffer<uint8_t> npmRomReadBuffer(const CallbackInfo& info);
Number npmRomRead32(const CallbackInfo& info);
Number npmRomRead16(const CallbackInfo& info);
Number npmRomRead8(const CallbackInfo& info);

Value npmRomWriteBuffer(const CallbackInfo& info);
Value npmRomWrite32(const CallbackInfo& info);
Value npmRomWrite16(const CallbackInfo& info);
Value npmRomWrite8(const CallbackInfo& info);

// #########################################################
// ## SaveStates
// #########################################################

Value npmSaveStatesRefreshHack(const CallbackInfo& info);

// #########################################################
// ## NAPI Export
// #########################################################

Object M64B_Memory_Init(Env env, Object exports);

#endif