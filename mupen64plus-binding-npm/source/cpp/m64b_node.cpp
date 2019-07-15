#include <napi.h>
#include "m64b_core.h"
#include "m64b_interface.h"
#include "m64b_memory.h"

Napi::Object InitAll(Napi::Env env, Napi::Object exports) {
  M64B_Memory_Init(env, exports);
  M64B_Interface_Init(env, exports);
  return M64B_Core_Init(env, exports);
}

NODE_API_MODULE(NODE_GYP_MODULE_NAME, InitAll)