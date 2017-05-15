#pragma once

#include <memory>
#include <atomic>

#include "BinaryBuffer.h"
#include "Except.h"

namespace rw
{
namespace core
{

enum class ResourceType
{
    RAW,
    TEXTURE,
};

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


/**
 * The ResourceHandle is the only way the "user" of the Resource API will
 * access resources. The ResourceHandle class manages retain-counts, and
 * exposes the Resource itself through the Get<T>()-method.
 */
class ResourceHandle
{
public:
    // Use this constructor if you don't want to initialize a Resource just
    // yet, but still want to have a ResourceHandle allocated.
    ResourceHandle();

    // This constructor can only be used with non-NULL values for 'res'. If
    // you want to initialize an empty ResourceHandle, you need to use the
    // non-parameterized constructor.
    ResourceHandle(Resource *res);

    ~ResourceHandle();

    ResourceHandle(const ResourceHandle &other);
    void operator=(const ResourceHandle &other);

    // Releases the Resource, and NULLs out the reference.
    void Reset();

    // Throws an std::exception if the Resource is NULL.
    template<class ResT = Resource>
    ResT* Get()
    {
        static_assert(std::is_base_of<Resource, ResT>::value,
                "ResT must be a subclass of Resource");
        if (!_resource) {
            THROW("Attempt to reference uninitialized resource");
        }
        return (ResT*)_resource;
    }

    // Throws an std::exception if the Resource is NULL.
    template<class ResT = Resource>
    const ResT* Get() const
    {
        static_assert(std::is_base_of<Resource, ResT>::value,
                "ResT must be a subclass of Resource");
        if (!_resource) {
            THROW("Attempt to reference uninitialized resource");
        }
        return (const ResT*)_resource;
    }

private:
    Resource *_resource;
};

}
}

