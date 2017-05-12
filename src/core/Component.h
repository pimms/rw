#pragma once

#include "IEventReceiver.h"
#include "EventDispatch.h"
#include "TypeId.h"

#include <typeinfo>
#include <functional>
#include <memory>

namespace rw
{

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
        GetEventDispatch()->Subscribe<EvtT>(shared_from_this(), func);
    }

    /**
     * Given a method in your Component on the form:
     *  MyComponent::OnSomeEvent(const std::shared_ptr<SomeEvent> e);
     *
     * You can subscribe on SomeEvent by calling:
     *  Subscribe(&MyComponent::OnSomeEvent);
     */

    template<typename MyT, typename EvtT>
    void Subscribe(void (MyT::*method)(const std::shared_ptr<EvtT>))
    {
        static_assert(std::is_base_of<Component,MyT>::value,
                      "MyT must be a subclass of Component");
        static_assert(std::is_base_of<Event,EvtT>::value,
                      "EvtT must be a subclass of Event");

        std::function<void(const std::shared_ptr<EvtT>)> func;
        func = std::bind(method, (MyT*)this, std::placeholders::_1);
        GetEventDispatch()->Subscribe(shared_from_this(), func);
    }

private:
    std::shared_ptr<EventDispatch> GetEventDispatch() const;

    std::shared_ptr<GameObject> _gameObject;
};

/* ComponentId */
typedef TypeId ComponentId;

template<class CompT>
inline ComponentId GetComponentId()
{
    return ::rw::GetTypeId<Component, CompT>();
}

template<class CompT>
inline ComponentId GetComponentId(const CompT&)
{
    return ::rw::GetTypeId<Component, CompT>();
}

template<class CompT>
inline ComponentId GetComponentId(const std::shared_ptr<CompT>&)
{
    return ::rw::GetTypeId<Component, CompT>();
}

}
