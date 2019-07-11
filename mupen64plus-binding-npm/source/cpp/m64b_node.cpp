#include <napi.h>
#include "m64b_interface.h"
#include "m64b_memory.h"

Napi::Object InitAll(Napi::Env env, Napi::Object exports) {
  m64b_memory::Init(env, exports);
  return m64b_interface::Init(env, exports);
}

NODE_API_MODULE(NODE_GYP_MODULE_NAME, InitAll)