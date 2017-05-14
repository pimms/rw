#pragma once

#include <SFML/Graphics.hpp>

#include "Resource.h"
#include "ResourceManager.h"

namespace rw
{
namespace core
{

class Texture : public Resource
{
public:
    Texture(BinaryBuffer::Ptr buffer);
    ~Texture();

    bool Load() override;

private:
    sf::Texture _texture;
};

}
}
