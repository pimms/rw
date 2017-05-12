#include "KeyboardState.h"
#include "../event/InputEvents.h"

namespace rw
{
namespace handler
{

KeyboardState::KeyboardState(std::shared_ptr<EventDispatch> evtDisp):
    _eventDispatch(evtDisp)
{
    memset(_keystates, 0, sizeof(_keystates));
}

void KeyboardState::OnKeyDown(sf::Keyboard::Key key)
{
    if (!_keystates[(int)key]) {
        // Only raise event on the *first* trigger. Most systems send key-down
        // events continuously as the key is being held (like when you hold a key
        // down in a text editor).
        _eventDispatch->Raise(std::make_shared<event::KeyDownEvent>(key));
        _keystates[(int)key] = true;
    }
}

void KeyboardState::OnKeyUp(sf::Keyboard::Key key)
{
    if (_keystates[(int)key]) {
        _eventDispatch->Raise(std::make_shared<event::KeyUpEvent>(key));
        _keystates[(int)key] = false;
    }
}

}
}
