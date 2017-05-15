#pragma once

#include "../core/EventDispatch.h"
#include <SFML/Window.hpp>
#include <stdint.h>


namespace rw
{
namespace handler
{

class KeyboardState
{
private:
    std::shared_ptr<EventDispatch> _eventDispatch;

    // TODO: We can potentially improve this further by using a bitmap, but I'm really
    // not sure it will be faster or not, given that we have to perform 2 divisons for
    // each lookup.
    bool _keystates[sf::Keyboard::KeyCount];

public:
    KeyboardState(std::shared_ptr<EventDispatch> evtDisp);

    void OnKeyDown(sf::Keyboard::Key key);
    void OnKeyUp(sf::Keyboard::Key key);
};

}
}
