#pragma once
#ifndef _AUDIO_MANAGER_H_
#define _AUDIO_MANAGER_H_

#include "stdafx.h"

#include "OpenAl/al.h"
#include "OpenAl/alc.h"

class AudioClip;
class AudioSource;
class AudioListener;


class AudioManager
{
private:// Manager Variables
	ALCdevice* m_ALC_Device;
	ALCcontext* m_ALC_Context;	

	//To Handle the AudioClips buffers and info on the game on better way
	struct tAudioInfo
	{
		AudioClip* audioBuffer;
		ALuint audioID;		
		unsigned int iRefCount;// Reference counter to unload buffer if not used
		tAudioInfo() : audioBuffer(nullptr), audioID(0), iRefCount(0){}
	};
	
	// Collection of pairs of name image and renderable info. For memmory purposes.
	std::map<std::string, tAudioInfo> m_Audios;

	std::vector<AudioClip*> m_audio_clips;
	std::vector<AudioSource*> m_audio_sources;
	std::vector<AudioListener*>m_audio_listeners;
	

public:// Singleton Settings
	static AudioManager& GetInstance(); //Singleton
	AudioManager(AudioManager const&) = delete; //Delete the default constructor
	void operator = (AudioManager const&) = delete; // Delete the operator to avoid copy constructor

public://Manager Cycle
	void Init();
	void AudioUpdate();
	void Terminate();
	

public://Funcionality functions
	char* LoadWav(const char* fn, ALuint& chan, ALuint& samplerate, ALuint& bps, ALsizei& size);
	bool  IsBigEndian();
	int   ConvertToInt(char* buffer, int len);



	
public://auxiliar functions
		// Insert AudioClip object.
	void InsertAudioClip(AudioClip& _clip);
	// Delete AudioClip object.
	void DeleteAudioClip(AudioClip& _clip);

	// Insert PhysX object.
	void InsertAudioSource(AudioSource& _source);
	// Delete PhysX object.
	void DeleteAudioSource(AudioSource& _source);

	// Insert PhysX object.
	void InsertAudioListener(AudioListener& _listener);
	// Delete PhysX object.
	void DeleteAudioListener(AudioListener& _listener);

private:
	// Private constructor for singleton
	AudioManager() {};
	
	
};
#endif

