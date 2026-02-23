#include "AudioTrack.hpp"

#include <iostream>

AudioTrack::AudioTrack(std::string fileName)
	: volume{1.0f}, fadeIn{false}, fadeOut{false}
{
	audio = AEAudioLoadMusic(fileName.c_str());
	if (!AEAudioIsValidAudio(audio)) std::cout << "Unable to load audio file " << fileName << std::endl;

	audioGroup = AEAudioCreateGroup();
	if (!AEAudioIsValidGroup(audioGroup)) std::cout << "Unable to create audio group for " << fileName << std::endl;
}

AudioTrack::~AudioTrack()
{
	AEAudioUnloadAudioGroup(audioGroup);
	AEAudioUnloadAudio(audio);

	std::cout << "Successfully destroyed AudioTrack" << std::endl;
}

AEAudio AudioTrack::GetAEAudio() const
{
	return audio;
}

AEAudioGroup AudioTrack::GetAEAudioGroup() const
{
	return audioGroup;
}

float AudioTrack::GetVolume()const
{
	return volume;
}

bool AudioTrack::SetVolume(float vol)
{
	if (vol < 0.f || vol > 1.f)
	{
		std::cout << "Volume should be between 0.f to 1.f" << std::endl;
		return false;
	}

	volume = vol;
	AEAudioSetGroupVolume(audioGroup, volume);
	return true;
}

bool& AudioTrack::FadeIn()
{
	return fadeIn;
}

bool& AudioTrack::FadeOut()
{
	return fadeOut;
}

void AudioTrack::PlayTrack(bool loop) const
{
	AEAudioPlay(audio, audioGroup, 1.f, 1.f, loop);
}

void AudioTrack::StopTrack() const
{
	AEAudioStopGroup(audioGroup);
}
