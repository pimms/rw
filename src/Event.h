#pragma once

#include "TypeId.h"

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
inline EventId GetEventId(T*)
{
    return GetTypeId<Event, T>();
}

