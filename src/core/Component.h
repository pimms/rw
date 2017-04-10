#pragma once

#include "IEventReceiver.h"
#include "EventDispatch.h"
#include "TypeId.h"

#include <typeinfo>
#include <functional>
#include <memory>

class GameObject;

class Component : public IEventReceiver, public std::enable_shared_from_this<Component>
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
    virtual void OnAttach(std::shared_ptr<GameObject> obj);

    std::shared_ptr<GameObject> GetGameObject() const;

protected:
    /**
     * Called after the Component has been added to a GameObject. This is where
     * you should manage all your event subscriptions. This method can be called
     * multiple times during the life cycle of a Component, so be extremely
     * cautious in modifying the Component state.
     */
    virtual void RegisterSubscriptions() { }

    template<typename EvtT>
    void Subscribe(std::function<void(const std::shared_ptr<EvtT>)> func)
    {
        GetEventDispatch()->Subscribe<EvtT>(func);
    }

private:
    std::shared_ptr<EventDispatch> GetEventDispatch() const;

    std::shared_ptr<GameObject> _gameObject;
};

/* ComponentId */
typedef TypeId ComponentId;

template<class CompT>
inline ComponentId GetComponentId(const CompT&)
{
    return GetTypeId<Component, CompT>();
}

template<class CompT>
inline ComponentId GetComponentId(std::shared_ptr<CompT>)
{
    return GetTypeId<Component, CompT>();
}

