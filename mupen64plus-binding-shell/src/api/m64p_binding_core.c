#include "../internal/core_interface.h"
#include "m64p_binding_core.h"

EXPORT m64p_error CALL DoCommand(m64p_command Command, int ParamInt, void *ParamPtr)
{ 
	return (*CoreDoCommand)(Command, ParamInt, ParamPtr);
}