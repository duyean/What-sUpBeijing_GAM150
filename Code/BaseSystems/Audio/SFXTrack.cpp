#include "SFXTrack.hpp"

#include <iostream>

SFXTrack::SFXTrack(const std::string& fileName, AEAudioGroup& _group)
	: group(_group)
{
	audio = AEAudioLoadSound(fileName.c_str());
	if (!AEAudioIsValidAudio(audio)) std::cout << "Unable to load SFX track " << fileName << std::endl;
}

SFXTrack::~SFXTrack()
{
}

void SFXTrack::PlayTrack()
{
	AEAudioPlay(audio, group, 1.f, 1.f, 0);
}
