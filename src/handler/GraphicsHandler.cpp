#include "GraphicsHandler.h"

// std
#include <iostream>

namespace rw
{
namespace handler
{

GraphicsHandler::GraphicsHandler(std::shared_ptr<sf::RenderWindow> window):
    _window(window)
{
}

void GraphicsHandler::Update()
{
    _window->clear();
    for(auto & texture : _activeTextures)
    {
        Draw(texture.second);
    }
    _window->display();
}

void GraphicsHandler::AddTexture(std::string ID, std::string texture)
{
    if(_textures.find(ID) != _textures.end())
    {
        std::cout << "Texture " << ID << " already exist" << std::endl;
        return;
    }

    sf::Texture tex;
    if(!tex.loadFromFile(texture))
    {
        std::cout << "Error: failed to load texture " << texture << " as " << ID << std::endl;
    }

    std::cout << "Add texture " << texture << " as " << ID << std::endl;
    _textures.insert(std::make_pair(ID, tex));
}

void GraphicsHandler::AddActiveTexture(std::string ID)
{
    if(_textures.find(ID) != _textures.end())
    {
        _activeTextures.insert(std::make_pair(ID, _textures[ID]));
    }
}

void GraphicsHandler::RemoveActiveTexture(std::string ID)
{
    if(_activeTextures.find(ID) != _activeTextures.end())
    {
        _activeTextures.erase(ID);
    }
}

bool GraphicsHandler::IsActive(std::string ID)
{
    if(_activeTextures.find(ID) != _activeTextures.end())
    {
        return true;
    }
    return false;
}

//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤

void GraphicsHandler::Draw(sf::Texture texture)
{
    sf::Sprite sprite;
    sprite.setTexture(texture);
    _window->draw(sprite);
}

} // handler
} // rw
