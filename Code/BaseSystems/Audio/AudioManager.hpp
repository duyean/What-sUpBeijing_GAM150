#pragma once

#include "AudioTrack.hpp"
#include "SFXTrack.hpp"
#include "../Code/BaseSystems/Prefabs/SingletonPattern.hpp"

#include <map>

class AudioManager : public SingletonPattern<AudioManager>
{
	friend SingletonPattern<AudioManager>;

public:
	enum AUDIO_TYPE
	{
		AUDIO_MAINMENU_BGM = 0,
		AUDIO_BASECAMP_BGM,
		AUDIO_LEVEL1_BGM,
		AUDIO_LEVEL2_BGM,
		AUDIO_LEVEL3_BGM,
		AUDIO_BATTLE1_BGM,
		AUDIO_BATTLE2_BGM,
		AUDIO_BATTLEBOSS_BGM,
		AUDIO_TOTAL
	};

	enum SFX_TYPE
	{
		SFX_BUTTON_PRESS = 0,
		SFX_GAME_START,
		SFX_SELECT_SHOP,
		SFX_PURCHASE_SHOP,
		SFX_START_LEVEL,
		SFX_ATTACK_BASIC,
		SFX_ATTACK_SCORCH,
		SFX_ATTACK_EMPOWER,
		SFX_ATTACK_APS,
		SFX_ATTACK_FLAMESTRIKE,
		SFX_ATTACK_COMBUST,
		SFX_ATTACK_CATACLYSM,
		SFX_ATTACK_WATERSURGE,
		SFX_ATTACK_HYDRORUSH,
		SFX_ATTACK_TIDALWAVE,
		SFX_EFFECT_BURN,
		SFX_EFFECT_POISON,
		SFX_EFFECT_EMPOWER,
		SFX_EFFECT_EXPOSE,
		SFX_EFFECT_COMBUST,
		SFX_EFFECT_SUPERHEAT,
		SFX_EFFECT_WEAKEN,
		SFX_ENEMY_HURT,
		SFX_ENEMY_HURT2,
		SFX_ENEMY_DEATH,
		SFX_ENEMY_DEATH2,
		SFX_BATTLE_HURT,
		SFX_BATTLE_HURT2,
		SFX_BATTLE_DEATH,
		SFX_BATTLE_DEATH2,
		SFX_BATTLE_START,
		SFX_BATTLE_WIN,
		SFX_TOTAL
	};

public:
	// Constructor
	AudioManager();
	// Destructor
	~AudioManager();

	void AddTrack(AUDIO_TYPE type, std::string fileName);
	bool PlayTrack(AUDIO_TYPE id, bool fade) const;
	void StopTrack(AUDIO_TYPE id, bool fade) const;
	void StopAllTracks(bool fade, AUDIO_TYPE exception = AUDIO_TOTAL) const;
	void AddSFX(SFX_TYPE type, std::string fileName);
	void PlaySFX(SFX_TYPE id) const;
	void Update();
	float& BGMVolume();
	float& SFXVolume();

private:
	std::map<AUDIO_TYPE, AudioTrack*> tracks;
	std::map<SFX_TYPE, SFXTrack*> sfxs;
	AEAudioGroup sfxGroup;
	float bgmVol, sfxVol;
	float prevBgmVol, prevSfxVol;
};
