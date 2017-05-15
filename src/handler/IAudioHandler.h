#pragma once

// std
#include <string>

namespace rw
{
namespace handler
{

class IAudioHandler
{
public:
    virtual bool AddAudio(std::string ID, std::string file) = 0;
    virtual void Play(std::string ID) = 0;
    virtual void Pause() = 0;
    virtual void Stop() = 0;
    virtual bool IsPlaying() = 0;
};

} // handler
} // rw
