#ifndef _M64B_MEMORY_
#define _M64B_MEMORY_

#include <napi.h>
using namespace Napi;

// #########################################################
// ## RDRam Memory
// #########################################################

Uint8Array npmRdRamReadBuffer(const CallbackInfo& info);
Number npmRdRamRead64(const CallbackInfo& info);
Number npmRdRamReadU64(const CallbackInfo& info);
Number npmRdRamRead32(const CallbackInfo& info);
Number npmRdRamReadU32(const CallbackInfo& info);
Number npmRdRamRead16(const CallbackInfo& info);
Number npmRdRamRead8(const CallbackInfo& info);

Value npmRdRamWriteBuffer(const CallbackInfo& info);
Value npmRdRamWrite64(const CallbackInfo& info);
Value npmRdRamWriteU64(const CallbackInfo& info);
Value npmRdRamWrite32(const CallbackInfo& info);
Value npmRdRamWriteU32(const CallbackInfo& info);
Value npmRdRamWrite16(const CallbackInfo& info);
Value npmRdRamWrite8(const CallbackInfo& info);

// #########################################################
// ## Rom Memory
// #########################################################

Number npmRomRead64(const CallbackInfo& info);
Number npmRomReadU64(const CallbackInfo& info);
Number npmRomRead32(const CallbackInfo& info);
Number npmRomReadU32(const CallbackInfo& info);
Number npmRomRead16(const CallbackInfo& info);
Number npmRomRead8(const CallbackInfo& info);

Value npmRomWrite64(const CallbackInfo& info);
Value npmRomWriteU64(const CallbackInfo& info);
Value npmRomWrite32(const CallbackInfo& info);
Value npmRomWriteU32(const CallbackInfo& info);
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