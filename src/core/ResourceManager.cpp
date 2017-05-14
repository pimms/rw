#include "ResourceManager.h"

#include <stdexcept>

#ifdef WIN32
    // TODO: Handle Windows
#else
    #include <dirent.h>
#endif

#include "Texture.h"

namespace rw
{
namespace core
{


ResourceManager::ResourceManager(const std::string &rootPath):
    _rootPath(rootPath)
{
    UpdateIndex();
}

ResourceManager::~ResourceManager()
{
    Purge();
}

void ResourceManager::Purge()
{
    for (auto it = _resources.begin(); it != _resources.end(); it++) {
        if (it->second && it->second->GetRetainCount() <= 0) {
            it->second = nullptr;
        }
    }
}

void ResourceManager::UpdateIndex()
{
    IndexRecursively("");
}

ResourceHandle::Ptr ResourceManager::Load(ResourceType type, const std::string &path)
{
    std::map<std::string, Resource::Ptr>::iterator itPointer;
    itPointer = _resources.find(path);

    bool found = (itPointer != _resources.end());

    if (!found) {
        // Case insensitive search - this is slow AF, and can be sped up significantly
        // by storing the paths in upper-case during indexing, and map the insensitive
        // variant to the proprely cased name. Anyways, point of improvement for the future.
        auto it = _resources.begin();
        for (; it != _resources.end(); it++) {
            bool hit = true;
            if (it->first.length() == path.length()) {
                for (int i=0; i<(int)path.length(); i++) {
                    if (toupper(it->first[i]) != toupper(path[i])) {
                        hit = false;
                        break;
                    }
                }

                if (hit) {
                    itPointer = it;
                    found = true;
                    break;
                }
            }
        }
    }

    Resource *resource = nullptr;

    if (found) {
        if (itPointer->second) {
            resource = itPointer->second.get();
        } else {
            _resources[path] = std::move(LoadResource(type, path));
            resource = _resources[path].get();
        }
    }

    if (resource) {
        ResourceHandle::Ptr handle = ResourceHandle::Ptr(new ResourceHandle(resource));
        return handle;
    }

    return nullptr;
}

#ifdef WIN32
void ResourceManager::IndexRecursively(const std::string &path)
{
    throw std::runtime_error("");
}
#else
void ResourceManager::IndexRecursively(const std::string &path)
{
    DIR *dir = nullptr;

    dir = opendir((_rootPath + "/" + path).c_str());
    if (!dir) {
        return;
    }

    dirent *ent = nullptr;

    while ((ent = readdir(dir)) != nullptr) {
        if (ent->d_type == DT_DIR) {
            // Recurse the directory
            if (strcmp(ent->d_name, ".") && strcmp(ent->d_name, "..")) {
                // It's the recursive CALLER's responsibility to suffix the path with a
                // trailing slash.
                IndexRecursively(path + ent->d_name + "/");
            }
        } else if (ent->d_type == DT_REG) {
            // Add the file to the _resources map if no such entry
            // already exists. Keep in mind that re-indexing is allowed,
            // so we might already have added this file.
            // Also, add the filename as-is. We'll handle case sensitivity
            // when the resource is being requested.
            const std::string assetDir = path + ent->d_name;
            if (_resources.count(assetDir) != 0) {
                _resources[assetDir] = nullptr;
            }
        }
    }

    closedir(dir);
}
#endif

Resource::Ptr ResourceManager::LoadResource(ResourceType type, const std::string &path)
{
    const std::string filePath = _rootPath + "/" + path;
    Resource::Ptr resource = nullptr;


    try {
        BinaryBuffer::Ptr buf = BinaryBuffer::Ptr(new BinaryBuffer(filePath));

        switch (type) {
            case ResourceType::TEXTURE:
                resource = Resource::Ptr(new Texture(std::move(buf)));
                break;
            default:
                printf("No handler for resource type '%d', requested for resource '%s'\n",
                        (int)type, path.c_str());
                break;
        }

        if (resource && !resource->Load()) {
            throw std::runtime_error("Failed to load Resource: " + path);
        }

    } catch (std::exception ex) {
        // TODO: Use a proper logging system
        printf("Failed to load resource '%s': %s\n", path.c_str(), ex.what());
    }

    return resource;
}


}
}
