#pragma once

#include "Resource.h"

#include <string>

namespace rw
{
namespace core
{

class RawResource : public Resource
{
public:
    RawResource(BinaryBuffer::Ptr buffer);

    virtual bool Load() override;

    std::string GetAsString() const;
};

}
}

