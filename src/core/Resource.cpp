#include "Resource.h"
#include "ResourceManager.h"

namespace rw
{
namespace core
{

/*
==================
Resource
==================
*/
Resource::Resource(ResourceType type, BinaryBuffer::Ptr buffer):
    _type(type)
{
    _buffer = std::move(buffer);
}

Resource::~Resource()
{

}

void Resource::Retain()
{
    _retainCount++;
}

void Resource::Release()
{
    _retainCount--;
}

int Resource::GetRetainCount() const
{
    return _retainCount;
}

ResourceType Resource::GetType() const
{
    return _type;
}

const BinaryBuffer* Resource::GetBuffer() const
{
    return _buffer.get();
}


/*
==================
ResourceHandle
==================
*/
ResourceHandle::ResourceHandle(Resource *res):
    _resource(res)
{
    _resource->Retain();
}

ResourceHandle::~ResourceHandle()
{
    _resource->Release();
}


}
}

