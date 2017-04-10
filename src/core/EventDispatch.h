#pragma once

#include "Event.h"
#include "IEventReceiver.h"
#include "TypeId.h"

#include <functional>
#include <map>
#include <vector>
#include <mutex>
#include <memory>

namespace rw
{

class EventDispatch
{
public:
    using EventFirstResponder = std::function<void(const std::shared_ptr<Event>)>;
    struct EventSubscription
    {
        std::shared_ptr<IEventReceiver> receiver;
        EventFirstResponder responder;
    };

    template<class EType>
    void Raise(const std::shared_ptr<EType> event)
    {
        std::lock_guard<std::mutex> lock(_mutex);

        EventId id = GetEventId(event);

        if (_subs.count(id) != 0) {
            std::vector<EventSubscription> *vec;
            vec = &_subs[id];

            for (int i=0; i<(int)vec->size(); i++) {
                (*vec)[i].responder(event);
            }
        }
    }

    template<typename EType>
    void Subscribe(std::shared_ptr<IEventReceiver> recv, std::function<void(const std::shared_ptr<EType>)> cb)
    {
        std::lock_guard<std::mutex> lock(_mutex);
        static_assert(std::is_base_of<Event, EType>::value, "EType must be subclass of Event");

        EventSubscription sub;
        sub.receiver = recv;
        sub.responder = [=](const std::shared_ptr<Event> e) {
            std::shared_ptr<EType> cast;
            cast = std::static_pointer_cast<EType>(e);
            cb(cast);
        };

        EventId eid = GetEventId<EType>();
        if (_subs.count(eid) == 0) {
            _subs[eid] = std::vector<EventSubscription>();
        }
        _subs[eid].push_back(sub);
    }

    void UnsubscribeAll(std::shared_ptr<IEventReceiver> recv);

private:
    std::mutex _mutex;
    std::map<EventId, std::vector<EventSubscription>> _subs;
};

}
