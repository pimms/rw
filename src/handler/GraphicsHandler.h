#pragma once

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <memory>
#include <algorithm>

namespace rw
{
namespace handler
{

class GraphicsHandler
{
private:
    std::shared_ptr<sf::RenderWindow>   _window;
    std::map<std::string, sf::Texture>  _textures;
    std::map<std::string, sf::Texture>  _activeTextures;

public:
    GraphicsHandler(std::shared_ptr<sf::RenderWindow> window);
    void Update();
    void AddTexture(std::string ID, std::string texture);

    void AddActiveTexture(std::string ID);
    void RemoveActiveTexture(std::string ID);
    bool IsActive(std::string ID);

private:
    void Draw(sf::Texture texture);
};

} // handler
} // rw
