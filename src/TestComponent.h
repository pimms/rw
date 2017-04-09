#pragma once

#include "Component.h"
#include "TestEvent.h"

class TestComponent : public Component
{
public:

protected:
    virtual void RegisterSubscriptions() override;

private:
    void OnTestEvent(const TestEvent *evt);

};
