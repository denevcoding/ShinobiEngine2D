#pragma once
#ifndef _AUDIO_CLIP_H_
#define _AUDIO_CLIP_H_

#include "../lib/OpenAl/al.h"

class AudioClip
{
public://Constructors Destructors
	AudioClip();
	AudioClip(const char* _root);
	~AudioClip();
	
public://Member Variables
	ALuint m_bufferid;
	ALuint m_sampleRate;
	ALenum m_format; //Mono Stereo de cuantos bITS
	ALuint m_channel;
	ALuint m_bps;
	ALuint m_freq;
	ALsizei m_size;
	ALuint cantBuffer = 1;
	const ALvoid* m_data;

public://Getters Setters
	inline const ALuint& GetAudioID() const { return m_bufferid; }
	inline const ALuint& GetSampleRate() const { return m_sampleRate; }
	inline const ALuint& GetFormat() const { return m_format; }
	inline const ALuint& GetChannel() const { return m_channel; }
	inline const ALuint& GetBPS() const { return m_bps; }
	inline const ALuint& GetFreq() const { return m_freq; }
	inline const ALsizei& GetSize() const { return m_size; }
	inline const ALuint& GetCantBuffer() const { return cantBuffer; }
	inline const ALvoid* GetClipData() const { return m_data; }	
};
#endif

