#include "InputHandler.h"

namespace rw
{
namespace handler
{

InputHandler::InputHandler(std::shared_ptr<sf::Window> window):
    _window(window)
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
        case sf::Event::GainedFocus:
            std::cout << "Rogue Waters gained focus" << std::endl;
        case sf::Event::KeyPressed:
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

        default:
            break;
        }
    }
}

}
}
