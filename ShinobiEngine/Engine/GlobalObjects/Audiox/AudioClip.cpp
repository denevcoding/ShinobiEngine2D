#include "stdafx.h"
#include "AudioClip.h"

#include "../ShinobiEngine/Engine/Managerx/AudioManager.h"

AudioClip::AudioClip()
 : m_bufferid(0)
 , m_sampleRate(0)
 ,m_format(0)
 ,m_channel(0)
 ,m_bps(0)
 ,m_freq(0)
 ,m_size(0)
 ,cantBuffer(0)
 ,m_data(nullptr)
{
}


AudioClip::AudioClip(const char* _root)
{
    // Generate Buffers
    alGetError(); // clear error code 
	
    m_data = AudioManager::GetInstance().LoadWav(_root, m_channel, m_sampleRate, m_bps, m_size);
    alGenBuffers(1, &m_bufferid);
    //Cathing the errors
    if ((errno = alGetError()) != AL_NO_ERROR)
    {
        std::cout << "alGenBuffers :" << errno;
        return;
    }

    //Filling the format of the file
    if (m_channel == 1)
    {
        if (m_bps == 8)
        {
            m_format = AL_FORMAT_MONO8;
        }
        else
        {
            m_format = AL_FORMAT_MONO16;
        }
    }
    else
    {
        if (m_bps == 8)
        {
            m_format = AL_FORMAT_STEREO8;
        }
        else
        {
            m_format = AL_FORMAT_STEREO16;
        }
    }

    alBufferData(m_bufferid, m_format, m_data, m_size, m_sampleRate);

    //Registering the component from the Audio Manager
    AudioManager::GetInstance().InsertAudioClip(*this);
}



AudioClip::~AudioClip()
{
    delete[] m_data;
    alDeleteBuffers(1, &m_bufferid);
}