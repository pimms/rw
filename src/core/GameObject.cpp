#include "GameObject.h"
#include "Component.h"

#include <typeinfo>

GameObject::GameObject(EventDispatch *dispatch)
{
    _eventDispatch = dispatch;
}

GameObject::~GameObject()
{
    for (Component *c : _components) {
        c->OnAttach(nullptr);
    }
}

void GameObject::AddComponent(Component *component)
{
    // TODO: We may want to ensure that we're only ever adding
    // one of each component-type to each gameobject.
    _components.push_back(component);
}

EventDispatch* GameObject::GetEventDispatch() const
{
    return _eventDispatch;
}

