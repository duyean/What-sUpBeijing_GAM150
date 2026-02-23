#pragma once

#include "AudioTrack.hpp"
#include "../../Engine_WZBJ_Pak.hpp"

#include <map>

class AudioManager : public SoloBehavior
{
	enum AUDIO_TYPE
	{
		AUDIO_TEST = 0,
		AUDIO_TOTAL
	};

public:
	// Constructor
	AudioManager();

	bool AddTrack(AUDIO_TYPE type, std::string fileName);
	bool PlayTrack(AUDIO_TYPE id, bool fade) const;
	void StopTrack(AUDIO_TYPE id, bool fade) const;

	void awake() override;
	void init() override;
	void update() override;
	void fixedUpdate() override;
	void destroy() override;

private:
	std::map<AUDIO_TYPE, AudioTrack*> tracks;
};
