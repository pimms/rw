#include "GameObject.h"
#include "Component.h"

#include <typeinfo>

GameObject::GameObject(std::shared_ptr<EventDispatch> dispatch)
{
    _eventDispatch = dispatch;
}

GameObject::~GameObject()
{
    for (auto & c : _components) {
        c->OnAttach(nullptr);
    }
}

void GameObject::AddComponent(std::shared_ptr<Component> component)
{
    // TODO: We may want to ensure that we're only ever adding
    // one of each component-type to each gameobject.
    _components.push_back(component);
}

std::shared_ptr<EventDispatch> GameObject::GetEventDispatch() const
{
    return _eventDispatch;
}

