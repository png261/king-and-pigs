#include "SoundManager.hpp"

SoundManager* SoundManager::Instance()
{
    static SoundManager* const s_pInstance = new SoundManager;
    return s_pInstance;
}

SoundManager::SoundManager()
    : m_bMutedMusic(false)
    , m_bMutedSFX(false)
    , m_volume(100)
{
    this->setVolume(100);
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024);
}

SoundManager::~SoundManager()
{
    Mix_CloseAudio();
}

void SoundManager::clean()
{
    m_musicMap.clear();
    m_sfxMap.clear();
}

bool SoundManager::loadMusic(const std::string filename, const std::string soundID)
{
    Mix_Music* const pMusic = Mix_LoadMUS(filename.c_str());
    if (pMusic == nullptr) {
        return false;
    }
    m_musicMap[soundID] = pMusic;
    return true;
}

bool SoundManager::loadSFX(const std::string filename, const std::string soundID)
{
    Mix_Chunk* const pSFX = Mix_LoadWAV(filename.c_str());
    if (pSFX == nullptr) {
        return false;
    }
    m_sfxMap[soundID] = pSFX;
    return true;
}

void SoundManager::playMusic(const std::string soundID, const int loop)
{
    Mix_PlayMusic(m_musicMap[soundID], loop);
}

void SoundManager::playSFX(const std::string soundID, const int loop)
{
    Mix_PlayChannel(-1, m_sfxMap[soundID], loop);
}

void SoundManager::setVolume(const int percent)
{
    m_volume = std::min(100, std::max(0, percent));
    m_bMutedMusic = false;
    m_bMutedSFX = false;
    this->setVolumeMusic(m_volume);
    this->setVolumeSFX(m_volume);
}

void SoundManager::changeVolume(const int percent)
{
    this->setVolume(m_volume + percent);
}

void SoundManager::muteMusic()
{
    m_bMutedMusic = true;
    this->setVolumeMusic(0);
}

void SoundManager::muteSFX()
{
    m_bMutedSFX = true;
    this->setVolumeSFX(0);
}

void SoundManager::unMuteMusic()
{
    m_bMutedMusic = false;
    this->setVolumeMusic(m_volume);
}

void SoundManager::unMuteSFX()
{
    m_bMutedSFX = false;
    this->setVolumeSFX(m_volume);
}

void SoundManager::toggleMuteMusic()
{
    if (this->isMutedMusic()) {
        this->unMuteMusic();
    } else {
        this->muteMusic();
    }
}

void SoundManager::toggleMuteSFX()
{
    if (this->isMutedSFX()) {
        this->unMuteSFX();
    } else {
        this->muteSFX();
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
