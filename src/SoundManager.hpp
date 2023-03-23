#pragma once

#include <map>
#include <string>
#include "SDL.hpp"

// music: .ogg
// sfx: .wav

class SoundManager
{
public:
    static SoundManager* Instance();

    bool loadSFX(const std::string filename, const std::string soundID);
    bool loadMusic(const std::string filename, const std::string soundID);

    void playSFX(const std::string soundID, const int loop = 0);
    void playMusic(const std::string soundID, const int loop = 0);

    void clean();

private:
    SoundManager();
    ~SoundManager();

    std::map<std::string, Mix_Music*> m_musicMap;
    std::map<std::string, Mix_Chunk*> m_sfxMap;
};
