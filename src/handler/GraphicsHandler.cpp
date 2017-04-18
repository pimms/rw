#include <iostream>

#include "GraphicsHandler.h"

static std::string RESOURCES = "../resources/images/";

namespace rw
{
namespace handler
{

GraphicsHandler::GraphicsHandler(std::shared_ptr<sf::RenderWindow> window):
    _window(window)
{
}

void GraphicsHandler::UpdateGraphics()
{
    _window->clear();
    Draw();
    _window->display();
}

void GraphicsHandler::Draw()
{
    sf::Texture texture;
    if(!texture.loadFromFile(RESOURCES + "ball.png"))
    {
        std::cout << "Error: failed to load image" << std::endl;
    }

    sf::Sprite sprite;
    sprite.setTexture(texture);

    _window->draw(sprite);
}

} // handler
} // rw
