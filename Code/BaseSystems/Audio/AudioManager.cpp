#include "AudioManager.hpp"

#include <iostream>

AudioManager::AudioManager()
{
	sfxGroup = AEAudioCreateGroup();
}

AudioManager::~AudioManager()
{
	for (std::pair<AUDIO_TYPE, AudioTrack*> pair : tracks)
		delete pair.second;
	AEAudioUnloadAudioGroup(sfxGroup);
}

void AudioManager::AddTrack(AUDIO_TYPE type, std::string fileName)
{
	tracks.insert(std::pair<AUDIO_TYPE, AudioTrack*>{type, new AudioTrack(fileName)});
}

bool AudioManager::PlayTrack(AUDIO_TYPE id, bool fade = false) const
{
	if (!AEAudioIsValidAudio(tracks.find(id)->second->GetAEAudio()))
	{
		std::cout << "Track does not have a valid AEAudio. Unable to play track." << std::endl;
		return false;
	}
	if (!AEAudioIsValidGroup(tracks.find(id)->second->GetAEAudioGroup()))
	{
		std::cout << "Track does not have a valid AEAudioGroup. Unable to play track." << std::endl;
		return false;
	}

	AudioTrack* track = tracks.find(id)->second;
	if (fade)
	{
		track->SetVolume(0.f);
		track->FadeIn() = true;
	}
	track->PlayTrack();
	std::cout << "Playing track..." << std::endl;
	return true;
}

void AudioManager::StopTrack(AUDIO_TYPE id, bool fade = false) const
{
	AudioTrack* track = tracks.find(id)->second;
	if (fade)
		track->FadeOut() = true;
	else
		track->StopTrack();
}

void AudioManager::AddSFX(SFX_TYPE type, std::string fileName)
{
	sfxs.insert(std::pair<SFX_TYPE, SFXTrack*>{type, new SFXTrack(fileName, sfxGroup)});
}

void AudioManager::PlaySFX(SFX_TYPE id) const
{
	sfxs.find(id)->second->PlayTrack();
}

