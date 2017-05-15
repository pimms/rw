#include <SFML/Audio.hpp>
#include <memory>

#include "handler/InputHandler.h"
#include "handler/GraphicsHandler.h"
#include "core/EventDispatch.h"

int main()
{
    auto eventDispatch = std::make_shared<rw::EventDispatch>();
    auto window = std::make_shared<sf::RenderWindow>(sf::VideoMode(800, 600), "Rogue Waters");
    auto inputHandler = std::make_shared<rw::handler::InputHandler>(window, eventDispatch);
    auto graphicsHandler = std::make_shared<rw::handler::GraphicsHandler>(window);

    graphicsHandler->AddTexture("ball", "../resources/images/ball.png");
    graphicsHandler->AddActiveTexture("ball");

    while (window->isOpen())
    {
        inputHandler->UpdateInput();
        graphicsHandler->UpdateGraphics();
    }
    return EXIT_SUCCESS;
}
