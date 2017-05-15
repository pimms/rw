#include "../core/Event.h"
#include <SFML/Window.hpp>

namespace rw
{

// Hide the fact that we're using SFML from the users of
// the events.... somewhat.
typedef sf::Keyboard::Key Key;

namespace event
{

class KeyDownEvent : public Event
{
private:
    Key _key;
public:
    KeyDownEvent(Key key);
    Key GetKey() const;
};

class KeyUpEvent: public Event
{
private:
    Key _key;
public:
    KeyUpEvent(Key key);
    Key GetKey() const;
};

}
}

