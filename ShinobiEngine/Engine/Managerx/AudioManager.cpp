#include "stdafx.h"
#include "AudioManager.h"

#include "../GlobalObjects/Audiox/AudioClip.h"
#include "../GameObjectx/Components/AudioComponents/AudioListener.h"
#include "../GameObjectx/Components/AudioComponents/AudioSource.h"


AudioManager& AudioManager::GetInstance()
{
	// TODO: insert return statement here
	static AudioManager AudioEngine;
	return AudioEngine;
}


//Initialize Engine
void AudioManager::Init()
{
    // Initialization
    m_ALC_Device = alcOpenDevice(NULL); // select the "preferred device" 

    if (m_ALC_Device)
    {
        m_ALC_Context = alcCreateContext(m_ALC_Device, NULL);
        alcMakeContextCurrent(m_ALC_Context);
    }
}

void AudioManager::AudioUpdate()
{
    // RenderAudio();
}

//Clean the mess
void AudioManager::Terminate()
{
    //Liberamos todos los buffers
//for (auto itImg = m_Images.begin(); itImg != m_Images.end(); ++itImg) {
//    UnloadTexture(itImg->second.ImgTexture);
//}

    m_audio_listeners.clear();
    m_audio_sources.clear();
    m_audio_clips.clear();

    m_ALC_Context = alcGetCurrentContext();
    m_ALC_Device = alcGetContextsDevice(m_ALC_Context);
    alcMakeContextCurrent(NULL);
    alcDestroyContext(m_ALC_Context);
    alcCloseDevice(m_ALC_Device);
}



//AudioClips Vector
void AudioManager::InsertAudioClip(AudioClip& _clip)
{
    // Control if prev. inserted.
    for (const AudioClip* pAudioSourceObj : m_audio_clips) {
        if (pAudioSourceObj == &_clip) {
            return;
        }
    }
    m_audio_clips.push_back(&_clip);
}
void AudioManager::DeleteAudioClip(AudioClip& _clip)
{
    for (auto it = m_audio_clips.begin(); it != m_audio_clips.end(); ++it) {
        if (*it == &_clip) {
            m_audio_clips.erase(it);
            break;
        }
    }
}


//Audio Listener Vector
void AudioManager::InsertAudioListener(AudioListener& _listener)
{
    // Control if prev. inserted.
    for (const AudioListener* pAudioListenerObj : m_audio_listeners) {
        if (pAudioListenerObj == &_listener) {
            return;
        }
    }
    m_audio_listeners.push_back(&_listener);
}
void AudioManager::DeleteAudioListener(AudioListener& _listener)
{
    for (auto it = m_audio_listeners.begin(); it != m_audio_listeners.end(); ++it) {
        if (*it == &_listener) {
            m_audio_listeners.erase(it);
            break;
        }
    }
}


//AudioSource Vector
void AudioManager::InsertAudioSource(AudioSource& _source)
{
    // Control if prev. inserted.
    for (const AudioSource* pAudioSourceObj : m_audio_sources) {
        if (pAudioSourceObj == &_source) {
            return;
        }
    }
    m_audio_sources.push_back(&_source);
}
void AudioManager::DeleteAudioSource(AudioSource& _source)
{
    for (auto it = m_audio_sources.begin(); it != m_audio_sources.end(); ++it) {
        if (*it == &_source) {
            m_audio_sources.erase(it);
            break;
        }
    }
}





//Load files
char* AudioManager::LoadWav(const char* fn, ALuint& chan, ALuint& samplerate, ALuint& bps, ALsizei& size)
{
    char buffer[4];
    std::ifstream in(fn, std::ios::binary);
    in.read(buffer, 4);


    if (strncmp(buffer, "RIFF", 4) != 0)
    {
        std::cout << "this is not a valid WAVE file" << std::endl;
        return NULL;
    }

    in.read(buffer, 4);	  //Chunk ID
    in.read(buffer, 4);      //WAVE
    in.read(buffer, 4);      //fmt
    in.read(buffer, 4);      //16
    int subChunkSize = ConvertToInt(buffer, 4);
    in.read(buffer, 2);      //AudioFormat
    in.read(buffer, 2);      //Channels	
    chan = ConvertToInt(buffer, 2);
    in.read(buffer, 4);      //SampleRate
    samplerate = ConvertToInt(buffer, 4);
    in.read(buffer, 4);      //ByteRate
    in.read(buffer, 2);      //BlockAlign
    in.read(buffer, 2);      //BPS
    bps = ConvertToInt(buffer, 2);

    bool dataFound = false;
    while (!dataFound)
    {
        in.read(buffer, 1);
        if (buffer[0] == 'd')
        {
            in.read(buffer, 3);
            if (buffer[0] == 'a' && buffer[1] == 't' && buffer[2] == 'a')
            {
                dataFound = true;
            }
        }
    }

    in.read(buffer, 4);      //size
    size = ConvertToInt(buffer, 4);

    char* data = new char[size];
    in.read(data, size);


    return data;
}
bool AudioManager::IsBigEndian()
{
    int a = 1;
    return !((char*)&a)[0];
}
int AudioManager::ConvertToInt(char* buffer, int len)
{
    int a = 0;
    if (!IsBigEndian())
        for (int i = 0; i < len; i++)
            ((char*)&a)[i] = buffer[i];
    else
        for (int i = 0; i < len; i++)
            ((char*)&a)[3 - i] = buffer[i];
    return a;
}

