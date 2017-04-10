#pragma once

#include "TypeId.h"

#include <memory>

class Event
{
public:

private:
};

/* Event Helpers */
typedef TypeId EventId;

template<class T>
inline EventId GetEventId(const T&)
{
    return GetTypeId<Event, T>();
}

template<class T>
inline EventId GetEventId(std::shared_ptr<T>)
{
    return GetTypeId<Event, T>();
}

