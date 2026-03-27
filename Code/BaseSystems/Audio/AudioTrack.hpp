#pragma once

#include "AEAudio.h"

#include <string>

class AudioTrack
{
public:
	// Constructor
	AudioTrack(std::string fileName);
	// Destructor
	~AudioTrack();

	// Accessors/Mutators
	AEAudio GetAEAudio() const;
	AEAudioGroup GetAEAudioGroup() const;
	float GetVolume() const;
	bool SetVolume(float vol);
	void SetVolumeMult(float mult);
	bool& FadeIn();
	bool& FadeOut();

	void PlayTrack(bool loop = true) const;
	void StopTrack() const;

private:
	bool fadeIn, fadeOut;
	float volume;
	float volMult;
	AEAudio audio;
	AEAudioGroup audioGroup;
};
