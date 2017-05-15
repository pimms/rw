#pragma once

#include <memory>
#include <map>
#include <string>

#include "Resource.h"

namespace rw
{
namespace core
{

/* ResourceManager (RM) hides away the nasty loading and re-use of assets
 * used in RW. The RM handles translations of relative paths to the working
 * directory.
 *
 * The RM indexes all resources at creation, so any modifications to the file
 * hierarchy post-creation will cause issues. See ResourceManager::UpdateIndex.
 *
 * As a side-note, for silly-OS support, all resource paths are case-insensitive.
 * This is handled automatically behind the scenes, so capitalize your assets
 * however you like.
 */
class ResourceManager
{
public:
    typedef std::shared_ptr<ResourceManager> Ptr;

    // The ResourceManager is case-insensitive, but the 'rootPath' parameter
    // is NOT. Ensure that the rootPath has the correct capitalization!
    ResourceManager(const std::string &rootPath);
    ~ResourceManager();

    // Purge all unclaimed resources
    void Purge();

    // Update the asset index. Any new assets added to the directories will be
    // added, but resources that has been removed since the last index will not
    // be removed from the index if it already is loaded.
    void UpdateIndex();

    // Load a resource.
    //
    // @param type      The type of resource you are loading. This determines which
    //                  implementation of the Resource superclass will be initiated.
    //                  If the same resource is ever attempted loaded with different
    //                  type hints, an exception will be raised.
    // @param path      Path to the resource, relative to the root directory. While
    //                  the loading process is case insensitive, the search is MUCH
    //                  faster if you handle your casing properly.
    ResourceHandle::Ptr Load(ResourceType type, const std::string &path);

private:
    // The path parameter must be relative to the root directory. This means that
    // in order to kick off the recursive search, call it with an empty string.
    void IndexRecursively(const std::string &path);

    // Internal loading of Resources. Attempts to load the resource found at 'path'
    // into a Resource implementation of type 'type'.
    // If the loading fails for any reason, NULL is returned.
    Resource::Ptr LoadResource(ResourceType type, const std::string &path);

    std::map<std::string, Resource::Ptr> _resources;
    std::string _rootPath;
};

}
}
