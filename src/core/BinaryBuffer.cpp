#include "BinaryBuffer.h"

#include <cassert>

#include "Except.h"

namespace rw
{
namespace core
{

BinaryBuffer::BinaryBuffer(const std::string &filePath):
    _buffer(nullptr),
    _size(0)
{
    std::ifstream file(filePath, std::ios::binary);
    if (!file) {
        THROW("BinaryBuffer failed to open file: %s ", filePath.c_str());
    }

    LoadFromStream(file);
}

BinaryBuffer::BinaryBuffer(std::ifstream &file):
    _buffer(nullptr),
    _size(0)
{
    LoadFromStream(file);
}

BinaryBuffer::~BinaryBuffer()
{
    if (_buffer) {
        delete[] _buffer;
        _buffer = nullptr;
    }
}

void BinaryBuffer::LoadFromStream(std::ifstream &file)
{
    assert(!_buffer);
    assert(!_size);

    file.seekg(0, std::ios::end);
    _size = file.tellg();
    file.seekg(0, std::ios::beg);

    _buffer = new uint8_t[_size];
    if (!file.read((char*)_buffer, _size)) {
        THROW("BinaryBuffer failed to read content from std::ifstream");
    }
}

const uint8_t* BinaryBuffer::GetBuffer() const
{
    return _buffer;
}

size_t BinaryBuffer::GetSize() const
{
    return _size;
}


}
}
