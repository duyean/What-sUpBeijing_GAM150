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
	
	//AddSFX(SFX_BUTTON_PRESS, "Assets/SFX/BasicAttack.mp3");
	//AddSFX(SFX_GAME_START, "Assets/SFX/BasicAttack.mp3");
	//AddSFX(SFX_PURCHASE_SHOP, "Assets/SFX/BasicAttack.mp3");
	//AddSFX(SFX_START_LEVEL, "Assets/SFX/BasicAttack.mp3");
	AddSFX(SFX_ATTACK_BASIC, "Assets/SFX/BasicAttack.mp3");
	AddSFX(SFX_ATTACK_SCORCH, "Assets/SFX/ScorchAttack.mp3");
	AddSFX(SFX_ATTACK_EMPOWER, "Assets/SFX/EmpowerAttack.mp3");
	AddSFX(SFX_ATTACK_APS, "Assets/SFX/ArmorPierceStrike.mp3");
	AddSFX(SFX_ATTACK_FLAMESTRIKE, "Assets/SFX/FlamestrikeAttack.mp3");
	//AddSFX(SFX_ATTACK_COMBUST, "Assets/SFX/FlamestrikeAttack.mp3");
	AddSFX(SFX_ATTACK_CATACLYSM, "Assets/SFX/CataclysmAttack.mp3");
	AddSFX(SFX_ATTACK_WATERSURGE, "Assets/SFX/WatersurgeAttack.mp3");
	AddSFX(SFX_ATTACK_HYDRORUSH, "Assets/SFX/HydrorushAttack.mp3");
	AddSFX(SFX_ATTACK_TIDALWAVE, "Assets/SFX/TidalwaveAttack.mp3");
	AddSFX(SFX_EFFECT_BURN, "Assets/SFX/BurnEffect.mp3");
	AddSFX(SFX_EFFECT_POISON, "Assets/SFX/PoisonEffect.mp3");
	//AddSFX(SFX_EFFECT_EMPOWER, "Assets/SFX/PoisonEffect.mp3");
	//AddSFX(SFX_EFFECT_EXPOSE, "Assets/SFX/PoisonEffect.mp3");
	//AddSFX(SFX_EFFECT_COMBUST, "Assets/SFX/PoisonEffect.mp3");
	//AddSFX(SFX_EFFECT_SUPERHEAT, "Assets/SFX/PoisonEffect.mp3");
	//AddSFX(SFX_EFFECT_WEAKEN, "Assets/SFX/PoisonEffect.mp3");
	AddSFX(SFX_ENEMY_HURT, "Assets/SFX/Hurt.mp3");
	AddSFX(SFX_ENEMY_HURT2, "Assets/SFX/Hurt2.mp3");
	AddSFX(SFX_ENEMY_DEATH, "Assets/SFX/Death.mp3");
	//AddSFX(SFX_ENEMY_DEATH2, "Assets/SFX/Death.mp3");
	AddSFX(SFX_BATTLE_HURT, "Assets/SFX/Hurt.mp3");
	AddSFX(SFX_BATTLE_HURT2, "Assets/SFX/Hurt2.mp3");
	AddSFX(SFX_BATTLE_DEATH, "Assets/SFX/Death.mp3");
	//AddSFX(SFX_BATTLE_DEATH2, "Assets/SFX/Death.mp3");
	AddSFX(SFX_BATTLE_START, "Assets/SFX/BattleStart.mp3");
	AddSFX(SFX_BATTLE_WIN, "Assets/SFX/BattleWin.mp3");
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

