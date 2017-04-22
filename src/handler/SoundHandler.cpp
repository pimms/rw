#include "SoundHandler.h"

// std
#include <algorithm>
#include <iostream>
#include <thread>

namespace rw
{
namespace handler
{

SoundHandler::SoundHandler():
    _sound(std::make_shared<sf::Sound>()),
    _buffers({}),
    _activeSound("")
{
}

SoundHandler::~SoundHandler()
{
}

bool SoundHandler::AddAudio(std::string ID, std::string file)
{
    if(_buffers.find(ID) != _buffers.end())
    {
        std::cout << "Buffer " << ID << " already exist" << std::endl;
        return false;
    }

    sf::SoundBuffer buffer;
    if(!buffer.loadFromFile(file))
    {
        std::cout << "Failed to add sound buffer " << file << std::endl;
        return false;
    }

    _buffers.insert(std::make_pair(ID, buffer));
    return true;
}

void SoundHandler::Play(std::string ID)
{
    if(_buffers.find(ID) != _buffers.end())
    {
        if(_activeSound.compare(ID) != 0)
        {
          _sound->setBuffer(_buffers[ID]);
          _activeSound = ID;
        }
        _sound->play();
    }
}

void SoundHandler::Pause()
{
    if(_sound->getStatus() == sf::SoundSource::Status::Playing)
    {
        _sound->pause();
    }
}

void SoundHandler::Stop()
{
    auto status = _sound->getStatus();
    if(status == sf::SoundSource::Status::Playing ||
       status == sf::SoundSource::Status::Paused)
    {
        _sound->stop();
    }
}

bool SoundHandler::IsPlaying()
{
    if(_sound->getStatus() == sf::SoundSource::Status::Playing)
    {
        return true;
    }
    return false;
}

} // handler
} // rw
