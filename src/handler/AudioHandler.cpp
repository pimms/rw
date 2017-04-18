#include "AudioHandler.h"

#include <algorithm>
#include <iostream>

namespace rw
{
namespace handler
{

AudioHandler::AudioHandler():
    _buffers({})
{
    _sound = std::make_shared<sf::Sound>();
    _music = std::make_shared<sf::Music>();
}

void AudioHandler::UpdateAudio()
{

}

bool AudioHandler::AddSoundBuffer(std::string name, std::string sound)
{
    if(_buffers.find(name) != _buffers.end())
    {
        std::cout << "Buffer " << name << " already exist" << std::endl;
        return false;
    }

    sf::SoundBuffer buffer;
    if(!buffer.loadFromFile(sound))
    {
        std::cout << "Failed to add sound buffer " << sound << std::endl;
        return false;
    }

    _buffers.insert(std::make_pair(name, buffer));
    return true;
}

void AudioHandler::PlayBuffer(std::string name)
{
    if(_buffers.find(name) != _buffers.end())
    {
        _sound->setBuffer(_buffers[name]);
        _sound->play();
    }
}

bool AudioHandler::PlayMusic(std::string music)
{
    if(!_music->openFromFile(music))
    {
        return false;
    }
    _music->play();
    return true;
}

} // handler
} // rw
