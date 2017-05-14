#include "Texture.h"

namespace rw
{
namespace core
{


Texture::Texture(BinaryBuffer::Ptr buf):
    Resource(ResourceType::TEXTURE, std::move(buf))
{

}

Texture::~Texture()
{

}

bool Texture::Load()
{
    const BinaryBuffer *buf = GetBuffer();
    return _texture.loadFromMemory(buf->GetBuffer(), buf->GetSize());
}


}
}
