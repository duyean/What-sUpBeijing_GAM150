#pragma once

#include "AEAudio.h"

#include <string>

class SFXTrack
{
public:
	// Constructor
	SFXTrack(const std::string& fileName, AEAudioGroup& _group);
	// Destructor
	~SFXTrack();

	// Functions
	void PlayTrack();
private:
	AEAudio audio;
	AEAudioGroup& group;
};

