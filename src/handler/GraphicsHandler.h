#pragma once

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <memory>

namespace rw
{
namespace handler
{

class GraphicsHandler
{
private:
    std::shared_ptr<sf::RenderWindow> _window;
public:
    GraphicsHandler(std::shared_ptr<sf::RenderWindow> window);
    void UpdateGraphics();
};

}
}
