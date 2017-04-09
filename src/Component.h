#pragma once

#include "IEventReceiver.h"
#include "EventDispatch.h"
#include "TypeId.h"

#include <typeinfo>
#include <functional>

class GameObject;

class Component : public IEventReceiver
{
public:
    Component();
    ~Component();

    /**
     * Called when the Component has been attached to a GameObject, and when
     * the Component is being removed from a GameObject. The 'obj' parameter
     * is respectively 'non-null' and 'null' for these cases.
     *
     * If you choose to override this method, ensure that you're also
     * calling the overridden method.
     */
    virtual void OnAttach(GameObject *obj);

    GameObject* GetGameObject() const;

protected:
    /**
     * Called after the Component has been added to a GameObject. This is where
     * you should manage all your event subscriptions. This method can be called
     * multiple times during the life cycle of a Component, so be extremely
     * cautious in modifying the Component state.
     */
    virtual void RegisterSubscriptions() { }

    template<typename EvtT>
    void Subscribe(std::function<void(const EvtT*)> func)
    {
        GetEventDispatch()->Subscribe<EvtT>(func);
    }

private:
    EventDispatch* GetEventDispatch() const;

    GameObject *_gameObject;
};

/* ComponentId */
typedef TypeId ComponentId;

template<class CompT>
inline ComponentId GetComponentId(const CompT&)
{
    return GetTypeId<Component, CompT>();
}

template<class CompT>
inline ComponentId GetComponentId(CompT*)
{
    return GetTypeId<Component, CompT>();
}

