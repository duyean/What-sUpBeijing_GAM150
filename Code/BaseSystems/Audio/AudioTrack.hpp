/*!************************************************************************
* \file AudioTrack.hpp
* \author Tai Yang Tat Bryson
* \par DP email: t.yangtatbryson\@digipen.edu
* \par Course: CSD1451-b
* \brief
*   This file implements functions regarding BGM tracks
**************************************************************************/

#pragma once

#include "AEAudio.h"

#include <string>

/*!***********************************************************************
* \class AudioTrack
* \brief
*  A track for BGM
*************************************************************************/
class AudioTrack
{
public:
	/*!***********************************************************************
	* \brief
	*  Overloaded constructor
	* \param[in] fileName
	*  File name of BGM asset
	*************************************************************************/
	AudioTrack(std::string fileName);
	/*!***********************************************************************
	* \brief
	*  Default destructor
	*************************************************************************/
	~AudioTrack();

	/*!***********************************************************************
	* \brief
	*  Getter for AEAudio
	* \return
	*  The AEAudio class of this AudioTrack
	*************************************************************************/
	AEAudio GetAEAudio() const;
	/*!***********************************************************************
	* \brief
	*  Getter for AEAudioGroup
	* \return
	*  The AEAudioGroup class of this AudioTrack
	*************************************************************************/
	AEAudioGroup GetAEAudioGroup() const;
	/*!***********************************************************************
	* \brief
	*  Gets the volume of this AudioTrack
	* \return
	*  The volume of the track
	*************************************************************************/
	float GetVolume() const;
	/*!***********************************************************************
	* \brief
	*  Sets the volume of this AudioTrack
	* \param[in] vol
	*  The new volume of the AudioTrack
	* \return
	*  If the volume has successfully been set
	*************************************************************************/
	bool SetVolume(float vol);
	/*!***********************************************************************
	* \brief
	*  Sets the multiplier of the volume of the AudioTrack
	* \param[in] mult
	*  The multiplier for the volume of the AudioTrack
	* \return
	*  void
	*************************************************************************/
	void SetVolumeMult(float mult);
	/*!***********************************************************************
	* \brief
	*  Accessor to the fadeIn boolean
	* \return
	*  A reference to fadeIn
	*************************************************************************/
	bool& FadeIn();
	/*!***********************************************************************
	* \brief
	*  Accessor to the fadeOut boolean
	* \return
	*  A reference to fadeOut
	*************************************************************************/
	bool& FadeOut();

	/*!***********************************************************************
	* \brief
	*  Plays the AEAudio
	* \param[in] loop
	*  If the track should loop
	* \return
	*  void
	*************************************************************************/
	void PlayTrack(bool loop = true) const;
	/*!***********************************************************************
	* \brief
	*  Stops the AEAudio
	* \return
	*  void
	*************************************************************************/
	void StopTrack() const;

private:
	// Booleans for fade in and out
	bool fadeIn, fadeOut;
	// Volume of the AudioTrack
	float volume;
	// Volume multiplier of the AudioTrack
	float volMult;
	// AEAudio to store the actual audio
	AEAudio audio;
	// AEAudioGroup of the audio
	AEAudioGroup audioGroup;
};
