#pragma once

#include<SFML/Window.hpp>

#include <iostream>
#include <memory>

namespace rw
{

class InputHandler
{
private:
    std::shared_ptr<sf::Window> _window;
public:
    InputHandler(std::shared_ptr<sf::Window> window);
    void HandleInput();
};

}
