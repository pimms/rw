#include <SFML/Audio.hpp>
#include <memory>

#include "handler/InputHandler.h"
#include "handler/GraphicsHandler.h"

int main()
{
    auto window = std::make_shared<sf::RenderWindow>(sf::VideoMode(800, 600), "Rogue Waters");
    auto inputHandler = std::make_shared<rw::handler::InputHandler>(window);
    auto graphicsHandler = std::make_shared<rw::handler::GraphicsHandler>(window);

    while (window->isOpen())
    {
        inputHandler->UpdateInput();
        graphicsHandler->UpdateGraphics();
    }
    return EXIT_SUCCESS;
}
