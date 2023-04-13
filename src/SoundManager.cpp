#include "SoundManager.hpp"
#include <SDL2/SDL_mixer.h>
#include "Log.hpp"

SoundManager& SoundManager::Instance()
{
    static SoundManager s_instance{};
    return s_instance;
}

SoundManager::SoundManager()
    : m_bMutedMusic(false)
    , m_bMutedSFX(false)
    , m_volume(100)
{
    setVolume(100);
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024);
}

void SoundManager::clean()
{
    for (auto& music : m_musicMap) {
        Mix_FreeMusic(music.second);
    }
    m_musicMap.clear();

    for (auto& sfx : m_sfxMap) {
        Mix_FreeChunk(sfx.second);
    }
    m_sfxMap.clear();
}

bool SoundManager::loadMusic(const std::string& path, const std::string& id)
{
    Mix_Music* const pMusic = Mix_LoadMUS(path.c_str());
    if (pMusic == nullptr) {
        Log::warning("can't load music: " + path);
        return false;
    }
    if (m_musicMap.find(id) != m_musicMap.end()) {
        return false;
    }
    m_musicMap[id] = pMusic;
    return true;
}

bool SoundManager::loadSFX(const std::string& path, const std::string& id)
{
    Mix_Chunk* const pSFX = Mix_LoadWAV(path.c_str());
    if (pSFX == nullptr) {
        Log::warning("can't load SFX: " + path);
        return false;
    }
    if (m_musicMap.find(id) != m_musicMap.end()) {
        return false;
    }
    m_sfxMap[id] = pSFX;
    return true;
}

void SoundManager::playMusic(const std::string& id, const int loop)
{
    if (m_musicMap.find(id) == m_musicMap.end()) {
        Log::warning("MusicID not exist: " + id);
        return;
    }
    Mix_PlayMusic(m_musicMap[id], loop);
}

void SoundManager::playSFX(const std::string& id, const int loop)
{
    if (m_sfxMap.find(id) == m_sfxMap.end()) {
        Log::warning("sfxID not exist: " + id);
        return;
    }
    Mix_PlayChannel(-1, m_sfxMap[id], loop);
}

void SoundManager::setVolume(const int percent)
{
    m_volume = std::min(100, std::max(0, percent));
    m_bMutedMusic = false;
    m_bMutedSFX = false;
    setVolumeMusic(m_volume);
    setVolumeSFX(m_volume);
}

void SoundManager::changeVolume(const int percent)
{
    setVolume(m_volume + percent);
}

void SoundManager::muteMusic()
{
    m_bMutedMusic = true;
    setVolumeMusic(0);
}

void SoundManager::muteSFX()
{
    m_bMutedSFX = true;
    setVolumeSFX(0);
}

void SoundManager::unMuteMusic()
{
    m_bMutedMusic = false;
    setVolumeMusic(m_volume);
}

void SoundManager::unMuteSFX()
{
    m_bMutedSFX = false;
    setVolumeSFX(m_volume);
}

void SoundManager::toggleMuteMusic()
{
    if (isMutedMusic()) {
        unMuteMusic();
    } else {
        muteMusic();
    }
}

void SoundManager::toggleMuteSFX()
{
    if (isMutedSFX()) {
        unMuteSFX();
    } else {
        muteSFX();
    }
}

bool SoundManager::isMutedMusic() const
{
    return m_bMutedMusic;
}

bool SoundManager::isMutedSFX() const
{
    return m_bMutedSFX;
}

void SoundManager::setVolumeMusic(const float percent)
{
    Mix_VolumeMusic(percent / 100 * MIX_MAX_VOLUME);
}

void SoundManager::setVolumeSFX(const float percent)
{
    Mix_MasterVolume(percent / 100 * MIX_MAX_VOLUME);
}

int SoundManager::getVolume() const
{
    return m_volume;
}
