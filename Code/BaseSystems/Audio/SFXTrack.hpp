/*!************************************************************************
* \file SFXTrack.hpp
* \author Tai Yang Tat Bryson
* \par DP email: t.yangtatbryson\@digipen.edu
* \par Course: CSD1451-b
* \brief
*   This file implements functions regarding SFX tracks
**************************************************************************/

#pragma once

#include "AEAudio.h"

#include <string>

/*!***********************************************************************
* \class SFXTrack
* \brief
*  A track for SFX
*************************************************************************/
class SFXTrack
{
public:
	/*!***********************************************************************
	* \brief
	*  Overloaded constructor
	* \param[in] fileName
	*  File name of SFX asset
	* \param[in] _group
	*  AEAudioGroup of the AEAudio
	*************************************************************************/
	SFXTrack(const std::string& fileName, AEAudioGroup& _group);
	/*!***********************************************************************
	* \brief
	*  Default destructor
	*************************************************************************/
	~SFXTrack();

	/*!***********************************************************************
	* \brief
	*  Plays the AEAudio
	* \return
	*  void
	*************************************************************************/
	void PlayTrack();
private:
	// AEAudio of the SFXTrack
	AEAudio audio;
	// AEAudioGroup of the audio
	AEAudioGroup& group;
};

