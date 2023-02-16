#include "SoundManager.hpp"
#include <SDL2/SDL_mixer.h>
#include <iostream>

SoundManager::SoundManager()
{
    Mix_OpenAudio(22050, AUDIO_S16, 2, (4096 / 2));
}

SoundManager::~SoundManager()
{
    Mix_CloseAudio();
}

bool isValidFileType(std::string filename, std::string filetype)
{
    return filename.substr(filename.find_last_of(".") + 1) == filetype;
}

bool SoundManager::loadMusic(std::string filename, std::string soundID)
{
    if (!isValidFileType(filename, "ogg")) {
        std::cout << "Filetype must be .ogg" << std::endl;
        return false;
    }

    Mix_Music* pMusic = Mix_LoadMUS(filename.c_str());
    if (pMusic == NULL) {
        return false;
    }
    m_musicMap[soundID] = pMusic;
    return true;
}

bool SoundManager::loadSFX(std::string filename, std::string soundID)
{
    if (!isValidFileType(filename, "wav")) {
        std::cout << "Filetype must be .wav" << std::endl;
        return false;
    }

    Mix_Chunk* pSFX = Mix_LoadWAV(filename.c_str());
    if (pSFX == NULL) {
        return false;
    }
    m_sfxMap[soundID] = pSFX;
    return true;
}

void SoundManager::playMusic(std::string soundID, int loop)
{
    Mix_PlayMusic(m_musicMap[soundID], loop);
}

void SoundManager::playSFX(std::string soundID, int loop)
{
    Mix_PlayChannel(-1, m_sfxMap[soundID], loop);
}
