#pragma once

// std
#include <memory>
#include <map>

// SFML
#include <SFML/Audio.hpp>

// rw
#include "AudioHandlerInterface.h"

namespace rw
{
namespace handler
{

class SoundHandler: public AudioHandlerInterface
{
private:
    std::shared_ptr<sf::Sound>              _sound;
    std::map<std::string, sf::SoundBuffer>  _buffers;
    std::string                             _activeSound;

public:
    SoundHandler();
    ~SoundHandler();

    bool AddAudio(std::string ID, std::string file) override;
    void Play(std::string ID) override;
    void Pause() override;
    void Stop() override;
    bool IsPlaying() override;
};

} // handler
} // rw
