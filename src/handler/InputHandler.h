#pragma once

// std
#include <iostream>
#include <memory>

// SFML
#include <SFML/Window.hpp>

// rw
#include "AudioHandlerInterface.h"
#include "../core/EventDispatch.h"
#include "KeyboardState.h"

namespace rw
{
namespace handler {

class InputHandler
{
private:
    std::shared_ptr<sf::Window> _window;
    std::shared_ptr<EventDispatch> _eventDispatch;
    KeyboardState _keyboardState;

public:
    InputHandler(std::shared_ptr<sf::Window> window, std::shared_ptr<EventDispatch> event);
    void Update();
};

} // handler
} // rw
