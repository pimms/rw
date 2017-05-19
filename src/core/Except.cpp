#include "Except.h"
#include <sstream>
#include <stdarg.h>

namespace rw
{

namespace Internal
{

void Throw(const char *file, const char *func, int line, const char *msg, ...)
{
    char formatted[4096];

    va_list ap;
    va_start(ap, msg);
    vsprintf(formatted, msg, ap);
    va_end(ap);

    std::stringstream ss;
    ss << "RW Exception\n";
    ss << "File:   " << file << "\n";
    ss << "Func:   " << func << "\n";
    ss << "Line:   " << line << "\n";
    ss << "What:   " << formatted;
    std::string s = ss.str();
    throw Exception(s);
}

}

}
