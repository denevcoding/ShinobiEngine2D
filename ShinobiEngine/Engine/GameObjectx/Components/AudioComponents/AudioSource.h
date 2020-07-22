#pragma once
#ifndef _AUDIO_SOURCE_H_
#define _AUDIO_SOURCE_H_
#include "../Component.h"

#include "OpenAl/al.h"

class AudioClip;
class Transform2D;
class Vec2;

class AudioSource : public Component
{
  //Inherited Variables
  //-Transform2D
  //-Owner
  //IsEnabled bool
  
public://Contructor Destructor
	AudioSource();
	AudioSource(Transform2D& _transform, AudioClip* _clip, bool _playOnAwake);
	~AudioSource();
	
public://Member Variables\	Transform2D* m_transform_2d;
	//Transform2D* m_transform_2d;
	ALuint  m_Sourceid;
	ALsizei m_cantSources;
	AudioClip* m_clip;

	//Audio Source Variables
	bool  m_playOnAwake;
	bool  m_loop;
	float m_pitch;
	float m_gain;	


public://OpenAL Functions  -- Falta loop y etc
	void Play();
	void Pause();
	void stop();
	bool isPlaying();

	
public:	//Source Functions
	void SetPosition(Vec2 _position);
	void SetOrientation(float _angle);
	void SetVelocity(Vec2 _velocity);

	
public://Component functions
	virtual void Update(double fTimeDif) override;
	//For component messages
	virtual void ReceiveMsg(const Message& message) override;
	//component Activation when it is running first time.
	virtual void Activate()override;
	//Component Deactivation before it is delete.
	virtual void Deactivate()override;


public://Gettes y Setters para un futuro
	
};

#endif


