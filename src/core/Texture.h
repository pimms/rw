#pragma once

#include <SFML/Graphics.hpp>

#include "Resource.h"

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

    sf::Vector2u GetSize() const;

private:
    sf::Texture _texture;
};

}
}
