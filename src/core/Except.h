#pragma once

#include <stdexcept>


typedef std::runtime_error Exception;

namespace Internal
{

void Throw(const char *file, const char *func, int line, const char *msg, ...);

}


#define THROW(MSG...) \
    Internal::Throw(__FILE__, __PRETTY_FUNCTION__, __LINE__, MSG)

