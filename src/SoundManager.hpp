#pragma once

#include <memory>
#include <string>
#include <unordered_map>
#include "SDL.hpp"

// music: .ogg
// sfx: .wav

class SoundManager
{
public:
    static SoundManager& Instance(); 
    SoundManager(SoundManager const&) = delete;
    SoundManager& operator=(SoundManager const&) = delete;

    bool loadSFX(const std::string& path, const std::string& id);
    bool loadMusic(const std::string& path, const std::string& id);

    void playSFX(const std::string& id, const int loop = 0);
    void playMusic(const std::string& id, const int loop = 0);

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
    void setVolumeMusic(const float percent);
    void setVolumeSFX(const float percent);

    bool m_bMutedMusic;
    bool m_bMutedSFX;
    float m_volume;

    std::unordered_map<std::string, Mix_Music*> m_musicMap;
    std::unordered_map<std::string, Mix_Chunk*> m_sfxMap;
};
