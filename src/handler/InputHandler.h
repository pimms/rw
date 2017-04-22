#pragma once

// std
#include <iostream>
#include <memory>

// SFML
#include <SFML/Window.hpp>

// rw
#include "IAudioHandler.h"

namespace rw
{
namespace handler {

class InputHandler
{
private:
    std::shared_ptr<sf::Window> _window;

public:
    InputHandler(std::shared_ptr<sf::Window> window);
    void UpdateInput();
};

} // handler
} // rw
