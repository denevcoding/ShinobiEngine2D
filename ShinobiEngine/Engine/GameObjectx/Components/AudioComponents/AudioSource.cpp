#include "stdafx.h"
#include "AudioSource.h"
#include "../../../Managerx/AudioManager.h"
#include "../../../GlobalObjects/Audiox/AudioClip.h"
#include "../Transform2D.h"


AudioSource::AudioSource()
:m_Sourceid(0)
,m_cantSources(0)
,m_clip(nullptr)
,m_playOnAwake(false)
,m_pitch(0)
,m_gain(0)
,m_loop(AL_FALSE)
{
	m_transform_2d = nullptr;
	m_isEnabled = false;
}

AudioSource::AudioSource(Transform2D& _transform, AudioClip* _clip, bool _playOnAwake)
: m_clip(_clip)
 ,m_pitch(1)
 ,m_gain(1)
 ,m_playOnAwake(_playOnAwake)
 ,m_loop(AL_FALSE)
{
	m_transform_2d = &_transform;
	m_isEnabled = true;
	
	m_cantSources = 1;

	// Generate Buffers
	alGetError(); // clear error code
	//Cathing the errors
	alGenSources(m_cantSources, &m_Sourceid);
	if ((errno = alGetError()) != AL_NO_ERROR)
	{
		std::cout << "alGenBuffers :" << errno;
		return;
	}

	//alSourcei(m_Sourceid, AL_MIN_GAIN, 0.f);
	//alSourcei(m_Sourceid, AL_MAX_GAIN, 1);
	alSourcei(m_Sourceid, AL_BUFFER, m_clip->m_bufferid);
	alSourcei(m_Sourceid, AL_PITCH, m_pitch);
	alSourcei(m_Sourceid, AL_GAIN, m_gain);

	alSourcei(m_Sourceid, AL_LOOPING, m_loop);

	SetPosition(Vec2(m_transform_2d->GetPos().GetX(), m_transform_2d->GetPos().GetY()));
	SetVelocity(Vec2(0, 0));
	//alSource3f(m_Sourceid, AL_DIRECTION, 0, 0, 0);

	/*alSourcef(m_Sourceid, AL_SEC_OFFSET, 1.0f);
	alSourcef(m_Sourceid, AL_SAMPLE_OFFSET, 1.0f);
	alSourcef(m_Sourceid, AL_BYTE_OFFSET, 1.0f);	*/

	
	//alSourcei(m_Sourceid, AL_SOURCE_RELATIVE, 0);
	//alSourcei(m_Sourceid, AL_SOURCE_TYPE, 1);

	//alSourcei(m_Sourceid, AL_MAX_DISTANCE, 100);
	//alSourcef(m_Sourceid, AL_ROLLOFF_FACTOR, 1.0f);
	//alSourcei(m_Sourceid, AL_REFERENCE_DISTANCE, 100);

	/*alSourcei(m_Sourceid, AL_CONE_OUTER_GAIN, 1);
	alSourcei(m_Sourceid, AL_CONE_INNER_ANGLE, 1);
	alSourcei(m_Sourceid, AL_CONE_OUTER_ANGLE, 1);*/	

	/*alSourcei(m_Sourceid, AL_BUFFERS_QUEUED, 1);
	alSourcei(m_Sourceid, AL_BUFFERS_PROCESSED, 1);*/

	
	//Registering the component from the Audio Manager
	AudioManager::GetInstance().InsertAudioSource(*this);

	//play the audio source from the initialization
	if (m_playOnAwake)
		this->Play();	
}




//To play an audio source, remember if want to change the sound have to change the clip
void AudioSource::Play()
{
	alGetError(); // clear error code
	if ((errno = alGetError()) != AL_NO_ERROR)
	{
		std::cout << "Error Playing Audiosource :" << errno;
		return;
	}
	alSourcePlay(m_Sourceid);
}

//To pause the current audio clip on the haudio source
void AudioSource::Pause()
{
	alGetError(); // clear error code
	if ((errno = alGetError()) != AL_NO_ERROR)
	{
		std::cout << "Error Playing Pausing :" << errno;
		return;
	}
	alSourcePause(m_Sourceid);
}

//Stop the current clip being played by current audio source
void AudioSource::stop()
{
	alGetError(); // clear error code
	if ((errno = alGetError()) != AL_NO_ERROR)
	{
		std::cout << "Error Stopping Audiosource :" << errno;
		return;
	}
	alSourceStop(m_Sourceid);
}

//Get if the audio source is playing something
bool AudioSource::isPlaying()
{
	//Desarrollar este metodo
	return false;
}





void AudioSource::SetPosition(Vec2 _position)
{
	alGetError(); // clear error code
	if ((errno = alGetError()) != AL_NO_ERROR)
	{
		std::cout << "Error Setting  Position:" << errno;
		return;
	}
	alSource3f(m_Sourceid, AL_POSITION, 0, 0, 0);
}

void AudioSource::SetOrientation(float _angle)
{
	alGetError(); // clear error code
	if ((errno = alGetError()) != AL_NO_ERROR)
	{
		std::cout << "Error Setting Orientation:" << errno;
		return;
	}	
	//alSourcefv(m_Sourceid, AL_DIRECTION, 0, 0, 0);
}

void AudioSource::SetVelocity(Vec2 _velocity)
{
	alGetError(); // clear error code
	if ((errno = alGetError()) != AL_NO_ERROR)
	{
		std::cout << "Error Setting the velocity :" << errno;
		return;
	}
	alSource3f(m_Sourceid, AL_VELOCITY, _velocity.GetX(), _velocity.GetX(), 0);
}

void AudioSource::Update(double fTimeDif)
{
	SetPosition(Vec2(m_transform_2d->GetPos().GetX(), m_transform_2d->GetPos().GetY()));
}

void AudioSource::ReceiveMsg(const Message& message)
{
}

void AudioSource::Activate()
{
	m_isEnabled = true;
}

void AudioSource::Deactivate()
{
	m_isEnabled = false;
}


AudioSource::~AudioSource()
{
	//Desregistering the component from the Audio Manager
	alDeleteSources(1, &m_Sourceid);
	AudioManager::GetInstance().DeleteAudioSource(*this);
}

