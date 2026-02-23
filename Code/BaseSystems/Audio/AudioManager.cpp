#include "AudioManager.hpp"

#include <iostream>

AudioManager::AudioManager()
{
}

bool AudioManager::AddTrack(AUDIO_TYPE type, std::string fileName)
{
	tracks.insert(std::pair<AUDIO_TYPE, AudioTrack*>{type, new AudioTrack(fileName)});
	return true;
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

void AudioManager::awake()
{
	AddTrack(AUDIO_TEST, "Assets/BGM/test.mp3");
}

void AudioManager::init()
{
}

void AudioManager::update()
{
	if (AEInputCheckTriggered(AEVK_1))
	{
		PlayTrack(AUDIO_TEST, true);
	}
	else if (AEInputCheckTriggered(AEVK_2))
	{
		StopTrack(AUDIO_TEST, true);
	}

	for (std::pair<AUDIO_TYPE, AudioTrack*> pair : tracks)
	{
		if (pair.second->FadeIn())
		{
			float newVol = AEClamp(pair.second->GetVolume() + float(AEFrameRateControllerGetFrameTime() * 0.5f), 0.f, 1.f);
			std::cout << "volume = " << newVol << std::endl;
			pair.second->SetVolume(newVol);
			if (newVol == 1.f) pair.second->FadeIn() = false;
		}
		else if (pair.second->FadeOut())
		{
			float newVol = AEClamp(pair.second->GetVolume() - float(AEFrameRateControllerGetFrameTime() * 0.5f), 0.f, 1.f);
			std::cout << "volume = " << newVol << std::endl;
			pair.second->SetVolume(newVol);
			if (newVol == 0.f)
			{
				pair.second->FadeOut() = false;
				pair.second->StopTrack();
			}
		}
	}
}

void AudioManager::fixedUpdate()
{
}

void AudioManager::destroy()
{
	for (std::pair<AUDIO_TYPE, AudioTrack*> pair : tracks)
	{
		delete pair.second;
	}
}
