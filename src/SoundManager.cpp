#include "SoundManager.hpp"
#include "Log.hpp"

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

bool SoundManager::loadMusic(const std::string path, const std::string id)
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

bool SoundManager::loadSFX(const std::string path, const std::string id)
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

void SoundManager::playMusic(const std::string id, const int loop)
{
    if (m_musicMap.find(id) == m_musicMap.end()) {
        Log::warning("MusicID not exist: " + id);
        return;
    }
    Mix_PlayMusic(m_musicMap[id], loop);
}

void SoundManager::playSFX(const std::string id, const int loop)
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
