#include <gtest/gtest.h>
#include "core/GameObject.h"
#include "core/EventDispatch.h"
#include "core/Component.h"

namespace rw
{
namespace test
{

class TestEvent : public Event
{
public:
    TestEvent(int n) { _n = n; }
    int GetN() const { return _n; }
private:
    int _n;
};

class TestComponent : public Component
{
public:
    TestComponent()
    {
        received = -1;
        registered = false;
    }

    void RegisterSubscriptions() override
    {
        registered = true;
        Subscribe(&TestComponent::OnEvent);
    }

    // Public for ease of access
    int received;
    bool registered;

private:
    void OnEvent(const std::shared_ptr<TestEvent> e)
    {
        received = e->GetN();
    }

};


TEST(GameObjectTests, DummyTest)
{
    std::shared_ptr<EventDispatch> dispatch = std::make_shared<EventDispatch>();
    std::shared_ptr<GameObject> gob = std::make_shared<GameObject>(dispatch);
    ASSERT_EQ(gob->GetEventDispatch(), dispatch);
}

TEST(GameObjectTests, ComponentSubscription)
{
    std::shared_ptr<EventDispatch> dispatch = std::make_shared<EventDispatch>();
    std::shared_ptr<GameObject> gob = std::make_shared<GameObject>(dispatch);

    std::shared_ptr<TestComponent> comp = std::make_shared<TestComponent>();
    gob->AddComponent(comp);
    ASSERT_TRUE(comp->registered);

    std::shared_ptr<TestEvent> evt = std::make_shared<TestEvent>(5);
    dispatch->Raise(evt);
    ASSERT_EQ(5, comp->received);
}

}
}
