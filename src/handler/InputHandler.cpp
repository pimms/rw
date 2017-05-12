#include "InputHandler.h"

// std
#include <time.h>
#include <chrono>
#include <thread>

namespace rw
{
namespace handler
{

InputHandler::InputHandler(std::shared_ptr<sf::Window> window,
                           std::shared_ptr<EventDispatch> evt):
    _window(window),
    _eventDispatch(evt)
{
}

void InputHandler::UpdateInput()
{
    sf::Event event;
    while (_window->pollEvent(event))
    {
        switch(event.type)
        {
        case sf::Event::Closed:
            _window->close();
            break;
        case sf::Event::LostFocus:
            std::cout << "Rogue Waters lost focus" << std::endl;
            break;
        case sf::Event::GainedFocus:
            std::cout << "Rogue Waters gained focus" << std::endl;
            break;
        case sf::Event::KeyReleased:
            _keyboardState.OnKeyUp(event.key.code);
            break;
        case sf::Event::KeyPressed:
            _keyboardState.OnKeyDown(event.key.code);

            switch(event.key.code)
            {
            case sf::Keyboard::Escape:
                std::cout << "Pressed key escape" << std::endl;
                break;
            case sf::Keyboard::W:
                std::cout << "Move up" << std::endl;
                break;
            case sf::Keyboard::S:
                std::cout << "Move down" << std::endl;
                break;
            case sf::Keyboard::A:
                std::cout << "Move left" << std::endl;
                break;
            case sf::Keyboard::D:
                std::cout << "Move right" << std::endl;
                break;
            default:
                break;
            }
            break;

        default:
            break;
        }
    }
}

} // handler
} // rw
