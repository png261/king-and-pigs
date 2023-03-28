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

    void setVolume(const int percent);
    void changeVolume(const int percent);
    int getVolume() const;

    void muteSFX();
    void unMuteSFX();
    void toggleMuteSFX();
    bool isMutedSFX() const;

    void muteMusic();
    void unMuteMusic();
    void toggleMuteMusic();
    bool isMutedMusic() const;

    void clean();

private:
    SoundManager();
    ~SoundManager();
    void setVolumeMusic(const float percent);
    void setVolumeSFX(const float percent);

    bool m_bMutedMusic;
    bool m_bMutedSFX;
    float m_volume;

    std::map<std::string, Mix_Music*> m_musicMap;
    std::map<std::string, Mix_Chunk*> m_sfxMap;
};
