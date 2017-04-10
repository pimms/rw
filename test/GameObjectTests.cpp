#include <gtest/gtest.h>
#include "core/GameObject.h"
#include "core/EventDispatch.h"

namespace rw
{

TEST(GameObjectTests, DummyTest)
{
    std::shared_ptr<EventDispatch> dispatch;
    std::shared_ptr<GameObject> gob = std::make_shared<GameObject>(dispatch);
    ASSERT_EQ(gob->GetEventDispatch(), dispatch);
}

}
