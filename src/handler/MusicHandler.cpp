#include "MusicHandler.h"

// std
#include <algorithm>
#include <iostream>
#include <thread>

namespace rw
{
namespace handler
{

MusicHandler::MusicHandler():
    _music(std::make_shared<sf::Music>()),
    _musicFiles({}),
    _activeFile("")
{
}

MusicHandler::~MusicHandler()
{
}

bool MusicHandler::AddAudio(std::string ID, std::string file)
{
    if(_musicFiles.find(ID) != _musicFiles.end())
    {
        std::cout << "Music file " << ID << " already exist" << std::endl;
        return false;
    }

    _musicFiles.insert(std::make_pair(ID, file));
    return true;
}

void MusicHandler::Play(std::string ID)
{
    if(_musicFiles.find(ID) != _musicFiles.end())
    {
        if(!_music->openFromFile(_musicFiles[ID]))
        {
            std::cout << "Failed to load music file " << ID << std::endl;
            return;
        }
        _music->play();
    }
}

void MusicHandler::Pause()
{
    _music->pause();
}

void MusicHandler::Stop()
{
    _music->stop();
}

bool MusicHandler::IsPlaying()
{
    if(_music->getStatus() == sf::SoundSource::Status::Playing)
    {
       return true;
    }
    return false;
}

} // handler
} // rw
