#include "CALAudioDriver.h"
#include "Utils.h"

namespace GameTutor
{
	CALAudioDriver::CALAudioDriver(): CAudioDriver(EAUDIO_DRIVER_OPENAL)
	{
		m_SoundMapping = new CLut<SALData*>();
	}

	CALAudioDriver::~CALAudioDriver() 
	{
		m_SoundMapping->DeallocateElementPointer();
		SAFE_DEL(m_SoundMapping);
	}

	bool CALAudioDriver::Initialize ()
	{
		ALCcontext *Context;
		ALCdevice *Device;

		Device = alcOpenDevice("DirectSound3D");
		if (Device == NULL)
		{
			return false;
		}

		//Create context(s)
		Context=alcCreateContext(Device,NULL);
		if (Context == NULL)
		{
			return false;
		}

		//Set active context
		alcMakeContextCurrent(Context);

		// Clear Error Code
		alGetError();


		// Position of the Listener.
		ALfloat ListenerPos[] = { 0.0, 0.0, 0.0 };

		// Velocity of the Listener.
		ALfloat ListenerVel[] = { 0.0, 0.0, 0.0 };

		// Orientation of the Listener. (first 3 elements are "at", second 3 are "up")
		// Also note that these should be units of '1'.
		ALfloat ListenerOri[] = { 0.0, 0.0, -1.0,  0.0, 1.0, 0.0 };

		alListenerfv(AL_POSITION,ListenerPos);
		alListenerfv(AL_VELOCITY,ListenerVel);
		alListenerfv(AL_ORIENTATION,ListenerOri);

		return true;
	}

	void CALAudioDriver::Destroy()
	{
		ForeachP(m_SoundMapping, SALData*, i)
		{
			alDeleteSources(1, &(i->Buffer));
			alDeleteSources(1, &(i->Source));
		}
	}

	void CALAudioDriver::Play (const char *name, bool isLoop)
	{
		SALData* data = 0;
		if (this->m_SoundMapping->GetElement(name, data))
		{
			if(alGetError() != AL_NO_ERROR)
				return;
			alSourcei (data->Source, AL_LOOPING, isLoop );
			if (!IsPlaying(data->Source))
			{
				alSourcei(data->Source, AL_SOURCE_RELATIVE, true);
				alSourcePlay(data->Source);
			}
		}

	}

	void CALAudioDriver::Pause (const char *name)
	{
		SALData* data = 0;
		if (this->m_SoundMapping->GetElement(name, data))
		{
			alSourcePause(data->Source);
		}
	}

	void CALAudioDriver::Stop (const char *name)
	{
		SALData* data = 0;
		if (this->m_SoundMapping->GetElement(name, data))
		{
			alSourceStop(data->Source);
		}
	}

	bool CALAudioDriver::IsPlaying (const char *name)
	{
		SALData* data = 0;
		if (this->m_SoundMapping->GetElement(name, data))
		{
			ALenum state = 0;
			alGetSourcei(data->Source, AL_SOURCE_STATE, &state);
			return (state == AL_PLAYING);
		}
		return false;
	}

	bool CALAudioDriver::IsPlaying (ALuint Source)
	{
		ALenum state = 0;
		alGetSourcei(Source, AL_SOURCE_STATE, &state);
		return (state == AL_PLAYING);
	}

	void CALAudioDriver::SetVolume(int vol)
	{
		TODO("CALAudioDriver::SetVolume is not implemented");
	}

	__INT32 CALAudioDriver::GetVolume()
	{
		TODO("CALAudioDriver::GetVolume is not implemented");
		return 0;
	}

	bool CALAudioDriver::OpenOgg (char *buf, int buf_size,unsigned int buffer)
	{
		int result;
		OggVorbis_File  oggStream;
		vorbis_info*    vorbisInfo = 0;
		vorbis_comment* vorbisComment = 0;
		ALenum format;

		if(!buf)
		{
			Log("[CALAudioDriver::OpenOgg] Input buffer is null");
			return 0;
		}

		SOggFile oggMemoryFile;
		oggMemoryFile.dataPtr = buf;
		oggMemoryFile.dataRead = 0;
		oggMemoryFile.dataSize = buf_size;
		
		ov_callbacks vorbisCallbacks =
		{
			VorbisRead,
			VorbisSeek,
			VorbisClose,
			VorbisTell
		};
		
		result = ov_open_callbacks(&oggMemoryFile, &oggStream, NULL, 0, vorbisCallbacks);
		//return false;
		if(result < 0)
		{
			Log("[CALAudioDriver::OpenOgg] Could not open Ogg memory stream");
		}

		vorbisInfo = ov_info(&oggStream, -1);
		vorbisComment = ov_comment(&oggStream, -1);

		if(vorbisInfo->channels == 1)
		{
			format = AL_FORMAT_MONO16;
		}
		else
		{
			format = AL_FORMAT_STEREO16;
		}
		// stream
		long long buffer_size = (long long)oggStream.pcmlengths;
		char *pcm = new char[buffer_size];
		int  size = 0;
		int  section;

		
		while(size < buffer_size)
		{
			result = ov_read(&oggStream, pcm + size, buffer_size - size, 0, 2, 1, &section);

			if(result > 0)
				size += result;
			else
				if(result < 0)
				{
					Log("[CALAudioDriver::OpenOgg] Error");
					VorbisError(result);
					return false;
				}
				else
					break;
		}

		if(size == 0)
		{
			Log("[CALAudioDriver::OpenOgg] Error: Can not decode ogg file");
			return false;
		}
		alBufferData(buffer, format, pcm, size, vorbisInfo->rate);
		ov_clear(&oggStream);
		delete pcm;
		return true;
	}
}