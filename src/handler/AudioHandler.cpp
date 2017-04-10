#include "AudioHandler.h"

#include <algorithm>

namespace rw
{
namespace handler
{

AudioHandler::AudioHandler()
{

}

void AudioHandler::UpdateAudio()
{

}

bool AudioHandler::AddSoundBuffer(std::string name, std::string sound)
{
    sf::SoundBuffer buffer;
    if(!buffer.loadFromFile(sound))
    {
        return false;
    }

    _buffers.insert(std::make_pair(name, buffer));
    return true;
}

void AudioHandler::PlayBuffer(std::string name)
{
    if(_buffers.find(name) != _buffers.end())
    {
        _sound.setBuffer(_buffers[name]);
        _sound.play();
    }
}

bool AudioHandler::PlayMusic(std::string music)
{
    if(!_music.openFromFile(music))
    {
        return false;
    }
    _music.play();
    return true;
}

} // handler
} // rw
