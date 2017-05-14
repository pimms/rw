#pragma once

#include <memory>
#include <atomic>

#include "BinaryBuffer.h"

namespace rw
{
namespace core
{

enum class ResourceType
{
    TEXTURE,
};

class ResourceManager;
class ResourceHandle;

/* Resource is an abstract superclass that handles arbitrary asset data.
 * The Resource class implies no context on the asset itself, all of this
 * must be handled by the implementations.
 *
 * Implementations should not do any work in the constructor. All interpretation,
 * initialization, and usage of the raw asset data should be performed in, or after
 * the Load()-call. The ResourceManager will call this method at an apporopriate time.
 */
class Resource
{
public:
    friend class ResourceHandle;

    typedef std::unique_ptr<Resource> Ptr;

    Resource(ResourceType type, BinaryBuffer::Ptr buffer);
    virtual ~Resource();

    int GetRetainCount() const;
    ResourceType GetType() const;

    const BinaryBuffer* GetBuffer() const;

    /* Load the resource. Implementations are expected to interpret the BinaryBuffer
     * (retrieved from GetBuffer()) and initialize their interpretations. If the
     * initialiazation succeeds, return true. Otherwise, return false.
     */
    virtual bool Load() = 0;

private:
    void Retain();
    void Release();

    std::atomic_int _retainCount;
    ResourceType _type;
    BinaryBuffer::Ptr _buffer;
};

class ResourceHandle
{
public:
    typedef std::shared_ptr<ResourceHandle> Ptr;

    ResourceHandle(Resource *res);
    ~ResourceHandle();

    template<class ResT = Resource>
    ResT* operator->()
    {
        static_assert(std::is_base_of<Resource, ResT>::value,
                "ResT must be a subclass of Resource");
        return (ResT*)_resource;
    }

    template<class ResT = Resource>
    const ResT* operator->() const
    {
        static_assert(std::is_base_of<Resource, ResT>::value,
                "ResT must be a subclass of Resource");
        return (const ResT*)_resource;
    }

private:
    Resource *_resource;
};

}
}

