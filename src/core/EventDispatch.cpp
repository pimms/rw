#include "EventDispatch.h"


void EventDispatch::Raise(const std::shared_ptr<Event> event)
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

void EventDispatch::UnsubscribeAll(std::shared_ptr<IEventReceiver> recv)
{
    std::lock_guard<std::mutex> lock(_mutex);

    for (auto &pair : _subs) {
        // This is a rather slow removal method, so if we're going to
        // be removing a lot of subscriptions at runtime, we need to
        // optimize this. An easy fix could be to use std::list as the
        // internal wrapper in _subs.
        for (int i=(int)pair.second.size()-1; i>=0; i--) {
            if (pair.second[i].receiver == recv) {
                pair.second.erase(pair.second.begin() + i);
            }
        }
    }
}
