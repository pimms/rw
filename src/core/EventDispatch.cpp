#include "EventDispatch.h"

namespace rw
{

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

}
