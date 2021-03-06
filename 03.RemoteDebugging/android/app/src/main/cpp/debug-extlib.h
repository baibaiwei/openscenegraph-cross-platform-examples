
/*
This file is part of OpenSceneGraph cross-platform examples:
  https://github.com/OGStudio/openscenegraph-cross-platform-examples

Copyright (C) 2018 Opensource Game Studio

This software is provided 'as-is', without any express or implied
warranty.  In no event will the authors be held liable for any damages
arising from the use of this software.

Permission is granted to anyone to use this software for any purpose,
including commercial applications, and to alter it and redistribute it
freely, subject to the following restrictions:

1. The origin of this software must not be misrepresented; you must not
   claim that you wrote the original software. If you use this software
   in a product, an acknowledgment in the product documentation would be
   appreciated but is not required.
2. Altered source versions must be plainly marked as such, and must not be
   misrepresented as being the original software.
3. This notice may not be removed or altered from any source distribution.
*/

#ifndef OPENSCENEGRAPH_CROSS_PLATFORM_EXAMPLES_DEBUG_EXTLIB_H
#define OPENSCENEGRAPH_CROSS_PLATFORM_EXAMPLES_DEBUG_EXTLIB_H

// extlib-json+localeconv-android Start
// Work around Android not having localeconv() before API 21.
// We target API 14.
#include <clocale>

lconv *localeconv()
{
    static lconv lc;
    return &lc;
}
// extlib-json+localeconv-android End
// extlib-json+STL-android Start
// Work around Android not having several STL functions in std.

#include <string>
#include <sstream>

namespace std
{
using ::strtof;
using ::strtold;
using ::strtoll;
using ::strtoull;
using ::snprintf;

template <typename T>
inline std::string to_string(T value)
{
    std::ostringstream os;
    os << value;
    return os.str();
}

inline int stoi(const std::string &s, size_t *idx = 0, int base = 10)
{
    char *endptr = 0;
    int result = strtol(s.c_str(), &endptr, base);
    if (idx)
	{
        *idx = endptr - s.c_str();
    }
    return result;
}

}
// extlib-json+STL-android End

// extlib-json Start
#include <nlohmann/json.hpp>
// extlib-json End

#endif // OPENSCENEGRAPH_CROSS_PLATFORM_EXAMPLES_DEBUG_EXTLIB_H

