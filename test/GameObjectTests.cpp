#include <gtest/gtest.h>
#include "core/GameObject.h"
#include "core/EventDispatch.h"

TEST(GameObjectTests, DummyTest)
{
    EventDispatch dispatch;
    GameObject *gob = new GameObject(&dispatch);
    ASSERT_EQ(gob->GetEventDispatch(), &dispatch);
}
