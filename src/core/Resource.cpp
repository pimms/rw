#include "Resource.h"

#include "Except.h"

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
    _type(type),
    _retainCount(0)
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
ResourceHandle::ResourceHandle():
    _resource(nullptr)
{

}

ResourceHandle::ResourceHandle(Resource *res):
    _resource(res)
{
    if (!_resource) {
        THROW("Cannot initialize with a NULL Resource - use the non-parameterized ctor!");
    }

    _resource->Retain();
}

ResourceHandle::~ResourceHandle()
{
    if (_resource) {
        _resource->Release();
    }
}

ResourceHandle::ResourceHandle(const ResourceHandle &other)
{
    _resource = other._resource;

    if (_resource) {
        _resource->Retain();
    }
}

void ResourceHandle::operator=(const ResourceHandle &other)
{
    if (_resource) {
        _resource->Release();
    }

    _resource = other._resource;

    if (_resource) {
        _resource->Retain();
    }
}

void ResourceHandle::Reset()
{
    if (_resource) {
        _resource->Release();
        _resource = nullptr;
    }
}


}
}

