#include <gtest/gtest.h>
#include "GameObject.h"
#include "EventDispatch.h"

TEST(GameObjectTests, DummyTest)
{
    EventDispatch dispatch;
    GameObject *gob = new GameObject(&dispatch);
    ASSERT_EQ(gob->GetEventDispatch(), &dispatch);
}
