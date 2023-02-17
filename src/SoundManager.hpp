#ifndef SOUND_MANAGER_HPP
#define SOUND_MANAGER_HPP

#include <map>
#include <string>
#include "SDL.hpp"

// music: .ogg
// sfx: .wav

class SoundManager
{
public:
    static SoundManager* Instance();

    bool loadSFX(std::string filename, std::string soundID);
    bool loadMusic(std::string filename, std::string soundID);

    void playSFX(std::string soundID, int loop = 0);
    void playMusic(std::string soundID, int loop = 0);

private:
    SoundManager();
    ~SoundManager();

    std::map<std::string, Mix_Music*> m_musicMap;
    std::map<std::string, Mix_Chunk*> m_sfxMap;
};

#endif
