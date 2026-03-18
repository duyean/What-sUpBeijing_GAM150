#include "AudioManager.hpp"

#include <iostream>
#include <AEMath.h>
#include <AEFrameRateController.h>

AudioManager::AudioManager()
{
	sfxGroup = AEAudioCreateGroup();

	AddTrack(AUDIO_MAINMENU_BGM, "Assets/BGM/MainMenu.mp3");
	AddTrack(AUDIO_BASECAMP_BGM, "Assets/BGM/HomeBase.mp3");
	AddTrack(AUDIO_LEVEL1_BGM, "Assets/BGM/Zone1.mp3");
	AddTrack(AUDIO_LEVEL2_BGM, "Assets/BGM/Zone2.mp3");
	AddTrack(AUDIO_LEVEL3_BGM, "Assets/BGM/Zone3.mp3");
	AddTrack(AUDIO_BATTLE1_BGM, "Assets/BGM/StandardBattle1.mp3");
	AddTrack(AUDIO_BATTLE2_BGM, "Assets/BGM/StandardBattle2.mp3");
	AddTrack(AUDIO_BATTLEBOSS_BGM, "Assets/BGM/BossBattle1.mp3");
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

void AudioManager::StopAllTracks(bool fade, AUDIO_TYPE exception) const
{
	for (std::pair<AUDIO_TYPE, AudioTrack*> pair : tracks)
	{
		if (pair.first == exception) continue;
		if (fade)
			pair.second->FadeOut() = true;
		else
			pair.second->StopTrack();
	}
}

void AudioManager::AddSFX(SFX_TYPE type, std::string fileName)
{
	sfxs.insert(std::pair<SFX_TYPE, SFXTrack*>{type, new SFXTrack(fileName, sfxGroup)});
}

void AudioManager::PlaySFX(SFX_TYPE id) const
{
	sfxs.find(id)->second->PlayTrack();
}

void AudioManager::Update()
{
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

