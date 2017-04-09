#pragma once

#include "Event.h"

class TestEvent
{
public:
    TestEvent(int num) { _num = num; }

    int GetNumber() const { return _num; }

private:
    int _num;
};
