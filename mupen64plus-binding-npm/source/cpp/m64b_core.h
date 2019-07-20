#ifndef _M64B_CORE_
#define _M64B_CORE_

#include <napi.h>
using namespace Napi;

Number npmCoreEmuState(const CallbackInfo& info);
Value npmSetFrameCallback(const CallbackInfo& info);
Value npmHookFrameCallback(const CallbackInfo& info);
 
// #########################################################
// ## NAPI Export
// #########################################################

Object M64B_Core_Init(Env env, Object exports);

#endif