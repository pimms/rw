#include "Component.h"
#include "Except.h"
#include "GameObject.h"
#include "EventDispatch.h"

Component::Component():
    _gameObject(nullptr)
{

}

Component::~Component()
{

}

void Component::OnAttach(GameObject *gameObject)
{
    if (_gameObject != nullptr) {
        THROW("Already added to a GameObject");
    }

    if (_gameObject != nullptr) {
        _gameObject = gameObject;
        RegisterSubscriptions();
    } else {
        _gameObject->GetEventDispatch()->UnsubscribeAll(this);
        _gameObject = nullptr;
    }
}

EventDispatch* Component::GetEventDispatch() const
{
    return _gameObject->GetEventDispatch();
}

