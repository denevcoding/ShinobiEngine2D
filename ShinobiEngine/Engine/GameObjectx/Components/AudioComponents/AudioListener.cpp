#include "stdafx.h"
#include "AudioListener.h"
#include "../Transform2D.h"
#include "../../../Managerx/AudioManager.h"

//Default constructor always initialice the component with anything
AudioListener::AudioListener()
:m_gain(0)

{
	m_transform_2d = nullptr;
	m_isEnabled = false;
}

AudioListener::AudioListener(Transform2D& _transform)
:m_gain(1)
{
	m_transform_2d = &_transform;
	m_isEnabled = true;

	SetPosition(Vec2(m_transform_2d->m_vPos.GetX(), m_transform_2d->m_vPos.GetY()));
	SetVelocity(Vec2(0, 0));
	
	AudioManager::GetInstance().InsertAudioListener(*this);
}




void AudioListener::SetPosition(Vec2 _position)
{
	alGetError(); // clear error code
	if ((errno = alGetError()) != AL_NO_ERROR)
	{
		std::cout << "Error Setting  Position:" << errno;
		return;
	}
	//alListeneri(AL_SOURCE_RELATIVE, false);
	alListener3f(AL_POSITION, 0, 0, 0);//Getting from the transform
	alListeneri(AL_GAIN, m_gain);//Getting from the transform	
}

void AudioListener::SetOrientation(float _angle)
{
	alGetError(); // clear error code
	if ((errno = alGetError()) != AL_NO_ERROR)
	{
		std::cout << "Error Setting  Position:" << errno;
		return;
	}	
}

void AudioListener::SetVelocity(Vec2 _velocity)
{
	alGetError(); // clear error code
	if ((errno = alGetError()) != AL_NO_ERROR)
	{
		std::cout << "Error Setting  Velocityy:" << errno;
		return;
	}
	alListener3f(AL_VELOCITY, _velocity.GetX(), _velocity.GetY(), 0);//Getting from the transform
}

void AudioListener::Update(double fTimeDif)
{
	SetPosition(Vec2(m_transform_2d->GetPos().GetX(), m_transform_2d->GetPos().GetY()));
}

void AudioListener::ReceiveMsg(const Message& message)
{
}

void AudioListener::Activate()
{
	m_isEnabled = true;
}

void AudioListener::Deactivate()
{
	m_isEnabled = false;
}



AudioListener::~AudioListener()
{
	//Desregistering the component from the Audio Manager
	AudioManager::GetInstance().DeleteAudioListener(*this);
}