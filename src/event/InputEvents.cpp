#include "InputEvents.h"

namespace rw
{
namespace event
{

/* KeyDownEvent */
KeyDownEvent::KeyDownEvent(Key key):
    _key(key) {}

Key KeyDownEvent::GetKey() const
{
    return _key;
}

/* KeyUpEvent */
KeyUpEvent::KeyUpEvent(Key k):
    _key(k) {}

Key KeyUpEvent::GetKey() const
{
    return _key;
}


}
}
