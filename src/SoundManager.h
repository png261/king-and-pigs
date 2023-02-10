#ifndef SOUND_MANAGER_H
#define SOUND_MANAGER_H

#include <SDL2/SDL_mixer.h>
#include <map>
#include <string>

// music: .ogg
// sfx: .wav

class SoundManager
{
public:
    static SoundManager* Instance()
    {
        static SoundManager* s_pInstance = new SoundManager;
        return s_pInstance;
    }

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
