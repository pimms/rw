#include <gtest/gtest.h>
#include "core/Event.h"
#include "core/EventDispatch.h"

namespace rw
{

class IntEvent : public Event
{
public:
    IntEvent(int n) { _n = n; }
    int GetN() const { return _n; }

private:
    int _n;
};

class StringEvent : public Event
{
public:
    StringEvent(std::string s) { _s = s; }
    std::string GetString() const { return _s; }

private:
    std::string _s;
};


class TestReceiver : public IEventReceiver
{
public:
    TestReceiver()
    {
        receivedInt = -1;
    }

    void OnStringEvent(const std::shared_ptr<StringEvent> sevt)
    {
        printf("Received StringEvent\n");
        receivedString = sevt->GetString();
    }

    void OnIntEvent(const std::shared_ptr<IntEvent> ievt)
    {
        printf("Received IntEvent\n");
        receivedInt = ievt->GetN();
    }

    std::string receivedString;
    int receivedInt;
};


TEST(EventTest, EventIdsDifferBetweenClasses)
{
    // Pretty much the whole foundation of the EventDispatch system
    // is based around these assumptions, so we'd be damned if they
    // weren't tested properly :)
    ASSERT_NE(GetEventId<IntEvent>(), GetEventId<Event>());
    ASSERT_NE(GetEventId<IntEvent>(), GetEventId<StringEvent>());

    // Also just to make sure the overridden functions work properly..
    IntEvent ie(5);
    StringEvent se("hei");
    ASSERT_NE(GetEventId(ie), GetEventId(se));
}

TEST(EventTest, SimpleDispatch)
{
    EventDispatch dispatch;
    std::shared_ptr<TestReceiver> irecv, srecv;
    irecv = std::make_shared<TestReceiver>();
    srecv = std::make_shared<TestReceiver>();

    // We'll need to wrap this cleanly in the final API, but this is the gist of what
    // should happen. This cryptic nonsense needs to be buried behind seven abstractions,
    // but once wrapped the final usage is very elegant.
    std::function<void(const std::shared_ptr<IntEvent>)> ifunc;
    ifunc = std::bind(&TestReceiver::OnIntEvent, irecv.get(), std::placeholders::_1);
    dispatch.Subscribe(irecv, ifunc);

    std::function<void(const std::shared_ptr<StringEvent>)> sfunc;
    sfunc = std::bind(&TestReceiver::OnStringEvent, srecv, std::placeholders::_1);
    dispatch.Subscribe(srecv, sfunc);

    // Start by ensuring that we're properly un-initialized.
    ASSERT_EQ(-1, irecv->receivedInt);
    ASSERT_EQ(-1, srecv->receivedInt);
    ASSERT_EQ("", srecv->receivedString);
    ASSERT_EQ("", irecv->receivedString);

    std::shared_ptr<IntEvent> ievt = std::make_shared<IntEvent>(1);
    std::shared_ptr<StringEvent> sevt = std::make_shared<StringEvent>("a");

    // TEST 1: Raise the int event. This should only trigger an event in the irecv
    dispatch.Raise(ievt);
    ASSERT_EQ(1, irecv->receivedInt);
    ASSERT_EQ(-1, srecv->receivedInt);

    // TEST 2: Raise the string event. Vice versa.
    dispatch.Raise(sevt);
    ASSERT_EQ("", irecv->receivedString);
    ASSERT_NE("", srecv->receivedString);

    // TEST 3: Unsubscribe irecv and raise ievt again. It should no longer update.
    ievt = std::make_shared<IntEvent>(2);
    dispatch.UnsubscribeAll(irecv);
    dispatch.Raise(ievt);
    ASSERT_EQ(1, irecv->receivedInt);
    ASSERT_EQ(-1, srecv->receivedInt);

    // TEST 4: Resubscribe the irecv and raise ievt yet again
    dispatch.Subscribe(irecv, ifunc);
    dispatch.Raise(ievt);
    ASSERT_EQ(2, irecv->receivedInt);
}

}
