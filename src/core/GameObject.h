#pragma once

#include <vector>
#include <memory>

namespace rw
{

class Component;
class EventDispatch;

class GameObject : public std::enable_shared_from_this<GameObject>
{
public:
    GameObject(std::shared_ptr<EventDispatch> dispatch);
    ~GameObject();

    void AddComponent(std::shared_ptr<Component> component);

    std::shared_ptr<EventDispatch> GetEventDispatch() const;

private:
    std::shared_ptr<EventDispatch> _eventDispatch;
    std::vector<std::shared_ptr<Component>> _components;
};
}
