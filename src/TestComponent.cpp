#include "TestComponent.h"
#include <stdio.h>

void TestComponent::RegisterSubscriptions()
{

}

void TestComponent::OnTestEvent(const TestEvent *evt)
{
    printf("TestEvent received: %d\n", evt->GetNumber());
}

