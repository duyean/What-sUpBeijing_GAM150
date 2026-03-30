/*!************************************************************************
* \file AudioManager.hpp
* \author Tai Yang Tat Bryson
* \par DP email: t.yangtatbryson\@digipen.edu
* \par Course: CSD1451-b
* \brief
*   This file implements functions regarding AudioManager to play BGM and SFX
**************************************************************************/

#pragma once

#include "AudioTrack.hpp"
#include "SFXTrack.hpp"
#include "../Code/BaseSystems/Prefabs/SingletonPattern.hpp"

#include <map>

/*!***********************************************************************
* \class AudioManager
* \brief
*  Manager for everything related to Audio
*************************************************************************/
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
	/*!***********************************************************************
	* \brief
	*  Default constructor
	*************************************************************************/
	AudioManager();
	/*!***********************************************************************
	* \brief
	*  Default destructor
	*************************************************************************/
	~AudioManager();

	/*!***********************************************************************
	* \brief
	*  Adds an AudioTrack into a map of all tracks
	* \param[in] type
	*  Type of AudioTrack
	* \param[in] fileName
	*  Name of the file Asset
	* \return
	*  void
	*************************************************************************/
	void AddTrack(AUDIO_TYPE type, std::string fileName);
	/*!***********************************************************************
	* \brief
	*  Plays a single AudioTrack
	* \param[in] id
	*  Type of AudioTrack to play
	* \param[in] fade
	*  If the AudioTrack should fade in
	* \return
	*  If the track is successfully played
	*************************************************************************/
	bool PlayTrack(AUDIO_TYPE id, bool fade) const;
	/*!***********************************************************************
	* \brief
	*  Stops a single AudioTrack
	* \param[in] id
	*  Type of AudioTrack to stop
	* \param[in] fade
	*  If the AudioTrack should fade out
	* \return
	*  void
	*************************************************************************/
	void StopTrack(AUDIO_TYPE id, bool fade) const;
	/*!***********************************************************************
	* \brief
	*  Stops all AudioTracks except for exception
	* \param[in] fade
	*  If the AudioTracks should fade out
	* \param[in] exception
	*  The AudioTrack to keep playing (if any)
	* \return
	*  void
	*************************************************************************/
	void StopAllTracks(bool fade, AUDIO_TYPE exception = AUDIO_TOTAL) const;
	/*!***********************************************************************
	* \brief
	*  Adds an SFXTrack into a map of all SFXs
	* \param[in] type
	*  Type of SFX
	* \param[in] fileName
	*  Name of the file Asset
	* \return
	*  void
	*************************************************************************/
	void AddSFX(SFX_TYPE type, std::string fileName);
	/*!***********************************************************************
	* \brief
	*  Plays a single SFX
	* \param[in] id
	*  Type of SFX to play
	* \return
	*  void
	*************************************************************************/
	void PlaySFX(SFX_TYPE id) const;
	/*!***********************************************************************
	* \brief
	*  Update function to update AudioTrack volumes
	* \return
	*  void
	*************************************************************************/
	void Update();
	/*!***********************************************************************
	* \brief
	*  Accessor function for bgmVol
	* \return
	*  A reference to bgmVol
	*************************************************************************/
	float& BGMVolume();
	/*!***********************************************************************
	* \brief
	*  Accessor function for sfxVol
	* \return
	*  A reference to sfxVol
	*************************************************************************/
	float& SFXVolume();

private:
	// A map of all AudioTracks
	std::map<AUDIO_TYPE, AudioTrack*> tracks;
	// A map of all SFXTracks
	std::map<SFX_TYPE, SFXTrack*> sfxs;
	// AEAudioGroup for SFX
	AEAudioGroup sfxGroup;
	// Volume of BGM and SFX
	float bgmVol, sfxVol;
	// Previous volume of BGM and SFX
	float prevBgmVol, prevSfxVol;
};
