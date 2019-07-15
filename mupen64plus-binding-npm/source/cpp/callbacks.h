#ifndef _M64B_CALLBACKS_
#define _M64B_CALLBACKS_

#include <napi.h>
using namespace Napi;

void Init_Callback_Frame(Function cb);
void M64P_Callback_Frame(unsigned int frameIndex);

#endif