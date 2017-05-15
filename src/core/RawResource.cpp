#include "RawResource.h"

namespace rw
{
namespace core
{

RawResource::RawResource(BinaryBuffer::Ptr buffer):
    Resource(ResourceType::RAW, std::move(buffer))
{

}

bool RawResource::Load()
{
    // well...
    return true;
}

std::string RawResource::GetAsString() const
{
    return std::string((const char*)GetBuffer()->GetBuffer(), GetBuffer()->GetSize());
}

}
}
