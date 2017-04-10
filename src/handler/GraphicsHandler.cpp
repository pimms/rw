#include "GraphicsHandler.h"

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
    _window->display();
}

}
}
