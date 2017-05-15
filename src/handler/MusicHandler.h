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

class MusicHandler : public AudioHandlerInterface
{
private:
    std::shared_ptr<sf::Music>          _music;
    std::map<std::string, std::string>  _musicFiles;
    std::string                         _activeFile;

public:
    MusicHandler();
    ~MusicHandler();

    bool AddAudio(std::string ID, std::string file) override;
    void Play(std::string ID) override;
    void Pause() override;
    void Stop() override;
    bool IsPlaying() override;
};

} // handler
} // rw
