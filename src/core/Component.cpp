#include "Component.h"
#include "Except.h"
#include "GameObject.h"
#include "EventDispatch.h"

namespace rw
{

Component::Component():
    _gameObject(nullptr)
{

}

Component::~Component()
{

}

void Component::OnAttach(std::shared_ptr<GameObject> gameObject)
{
    if (_gameObject != nullptr) {
        THROW("Already added to a GameObject");
    }

    if (gameObject != nullptr) {
        _gameObject = gameObject;
        RegisterSubscriptions();
    } else {
        _gameObject->GetEventDispatch()->UnsubscribeAll(shared_from_this());
        _gameObject = nullptr;
    }
}

std::shared_ptr<EventDispatch> Component::GetEventDispatch() const
{
    return _gameObject->GetEventDispatch();
}

}
