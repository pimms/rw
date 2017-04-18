#pragma once

#include <SFML/Audio.hpp>
#include <memory>
#include <map>
#include <string>

namespace rw
{
namespace handler
{

class AudioHandler
{
private:
    std::shared_ptr<sf::Sound> _sound;
    std::shared_ptr<sf::Music> _music;
    std::map<std::string, sf::SoundBuffer> _buffers;
public:
    AudioHandler();
    void UpdateAudio();
    bool AddSoundBuffer(std::string name, std::string sound);
    void PlayBuffer(std::string name);
    bool PlayMusic(std::string music);
};

} // handler
} // rw
