#pragma once

#include <vector>

class Component;
class EventDispatch;

class GameObject
{
public:
    GameObject(EventDispatch *dispatch);
    ~GameObject();

    void AddComponent(Component *component);

    EventDispatch* GetEventDispatch() const;

private:
    EventDispatch *_eventDispatch;
    std::vector<Component*> _components;
};
