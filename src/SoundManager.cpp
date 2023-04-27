#include "SoundManager.hpp"

#include "Log.hpp"

SoundManager& SoundManager::Instance()
{
    static SoundManager instance{};
    return instance;
}

SoundManager::SoundManager()
    : is_muted_music_(false)
    , is_muted_sfx_(false)
    , volume_(100)
{
    setVolume(100);
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024);
}

void SoundManager::clean()
{
    for (auto& music : musics_) {
        Mix_FreeMusic(music.second);
    }
    musics_.clear();

    for (auto& sfx : sfxs_) {
        Mix_FreeChunk(sfx.second);
    }
    sfxs_.clear();
}

bool SoundManager::loadMusic(const std::string& path, const std::string& id)
{
    Mix_Music* const pMusic = Mix_LoadMUS(path.c_str());
    if (pMusic == nullptr) {
        Log::warning("can't load music: " + path);
        return false;
    }
    if (musics_.find(id) != musics_.end()) {
        return false;
    }
    musics_[id] = pMusic;
    return true;
}

bool SoundManager::loadSFX(const std::string& path, const std::string& id)
{
    Mix_Chunk* const pSFX = Mix_LoadWAV(path.c_str());
    if (pSFX == nullptr) {
        Log::warning("can't load SFX: " + path);
        return false;
    }
    if (musics_.find(id) != musics_.end()) {
        return false;
    }
    sfxs_[id] = pSFX;
    return true;
}

void SoundManager::playMusic(const std::string& id, const int loop) const
{
    if (musics_.find(id) == musics_.end()) {
        Log::warning("MusicID not exist: " + id);
        return;
    }
    Mix_PlayMusic(musics_.at(id), loop);
}

void SoundManager::playSFX(const std::string& id, const int loop) const
{
    if (sfxs_.find(id) == sfxs_.end()) {
        Log::warning("sfxID not exist: " + id);
        return;
    }
    Mix_PlayChannel(-1, sfxs_.at(id), loop);
}

void SoundManager::setVolume(const int percent)
{
    volume_ = std::min(100, std::max(0, percent));
    is_muted_music_ = false;
    is_muted_sfx_ = false;
    setVolumeMusic(volume_);
    setVolumeSFX(volume_);
}

void SoundManager::changeVolume(const int percent)
{
    setVolume(volume_ + percent);
}

void SoundManager::muteMusic()
{
    is_muted_music_ = true;
    setVolumeMusic(0);
}

void SoundManager::muteSFX()
{
    is_muted_sfx_ = true;
    setVolumeSFX(0);
}

void SoundManager::unMuteMusic()
{
    is_muted_music_ = false;
    setVolumeMusic(volume_);
}

void SoundManager::unMuteSFX()
{
    is_muted_sfx_ = false;
    setVolumeSFX(volume_);
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
    return is_muted_music_;
}

bool SoundManager::isMutedSFX() const
{
    return is_muted_sfx_;
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
    return volume_;
}
