#pragma once

#include "TypeId.h"
#include <memory>

namespace rw
{

class Event
{
public:

private:
};

/* Event Helpers */
typedef TypeId EventId;

template<class T>
inline EventId GetEventId()
{
    return ::rw::GetTypeId<Event, T>();
}

template<class T>
inline EventId GetEventId(const T&)
{
    return ::rw::GetTypeId<Event, T>();
}

template<class T>
inline EventId GetEventId(const std::shared_ptr<T>)
{
    return ::rw::GetTypeId<Event, T>();
}

}
