#pragma once

#include <string>
#include <fstream>
#include <memory>
#include <stdint.h>

namespace rw
{
namespace core
{

class BinaryBuffer
{
public:
    typedef std::unique_ptr<BinaryBuffer> Ptr;

    BinaryBuffer(const std::string &filePath);
    BinaryBuffer(std::ifstream &file);
    ~BinaryBuffer();

    const uint8_t* GetBuffer() const;
    size_t GetSize() const;

private:
    void LoadFromStream(std::ifstream &file);

    uint8_t *_buffer;
    size_t _size;
};


}
}

