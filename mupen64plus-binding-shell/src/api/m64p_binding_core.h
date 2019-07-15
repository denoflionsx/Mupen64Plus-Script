#if !defined(__M64P_BINDING_CORE_H__)
#define __M64P_BINDING_CORE_H__

#include "m64p_types.h"

EXPORT m64p_error CALL DoCommand(m64p_command Command, int ParamInt, void *ParamPtr);

#endif