#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <memory>

#include "InputHandler.h"

int main()
{
    auto window = std::make_shared<sf::RenderWindow>(sf::VideoMode(800, 600), "Rogue Waters");
    auto inputHandler = std::make_shared<rw::InputHandler>(window);

    while (window->isOpen())
    {
        inputHandler->HandleInput();
        window->clear();
        window->display();
    }
    return EXIT_SUCCESS;
}
