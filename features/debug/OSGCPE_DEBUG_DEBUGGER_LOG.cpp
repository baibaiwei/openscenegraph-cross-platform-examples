FEATURE debug.h/Impl
#include "log.h"
#include "format.h"
#define OSGCPE_DEBUG_DEBUGGER_LOG_PREFIX "osgcpe::debug::Debugger(%p) %s"
#define OSGCPE_DEBUG_DEBUGGER_LOG(...) \
    osgcpe::log::logprintf( \
        OSGCPE_DEBUG_DEBUGGER_LOG_PREFIX, \
        this, \
        osgcpe::format::printfString(__VA_ARGS__).c_str() \
    )
