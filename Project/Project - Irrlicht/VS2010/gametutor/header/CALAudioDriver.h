#ifndef __CALAUDIODRIVER_H__
#define __CALAUDIODRIVER_H__
#include "Header.h"
#include "CAudioDriver.h"
#include "CLookupTableStr.h"
#include "CVorbisStreamPorting.h"

namespace GameTutor
{
	struct SALData
	{
		ALuint Buffer;
		ALuint Source;
		SALData():Buffer(0), Source(0){}
	};
	class CALAudioDriver: public CAudioDriver, public CSingleton<CALAudioDriver>, private CVorbisStreamPorting
	{
		friend class CSingleton<CALAudioDriver>;
	protected:
		CALAudioDriver();
	public:
		virtual ~CALAudioDriver();
		bool Initialize ();
		void Destroy();
		void Play(const char *name, bool isLoop);
		void Pause(const char *name);
		void Stop(const char *name);
		void SetVolume(int vol);
		__INT32 GetVolume();
		bool IsPlaying (const char *name);
		template <class IODriver> ALboolean Load(const char* fileName, EAudioMinetype minetype);
	private:
		template <class IODriver> bool OpenWave(const char *nameFile,unsigned int buffer);
		template <class IODriver> bool OpenOgg(const char *nameFile,unsigned int buffer);
		bool OpenOgg (char *buf, int buf_size,unsigned int buffer);
		bool IsPlaying (ALuint ID);
	private:
		CLut<SALData*> *m_SoundMapping;
	};


	template <class IODriver> ALboolean CALAudioDriver::Load(const char* fileName, EAudioMinetype minetype)
	{
		SALData *Source = new SALData;

		if (this->m_SoundMapping->GetElement(fileName, Source))
		{
			LogWarning("fileName %s has been already loaded. Ignore", fileName);
			return false;
		}

		// Load wav data into a buffer.
		alGenBuffers(1, &(Source->Buffer));

		if(alGetError() != AL_NO_ERROR)
			return AL_FALSE;

		bool isWav = false;
		bool isOgg = false;
		if (minetype == EAUDIOMINE_AUTO)
		{
			//Check sound format
			char ext[3];
			memcpy(ext, fileName + (strlen(fileName) - 3), 3);
			Str_ToLower(ext, 3);

			
			if (memcmp("wav", ext, 3) == 0)
			{
				isWav = true;
			}

			else if (memcmp("ogg", ext, 3) == 0)
			{
				isOgg = true;
			}
		}
		else if (minetype == EAUDIOMINE_WAV)
		{
			isWav = true;
		}
		else if (minetype == EAUDIOMINE_OGG)
		{
			isOgg = true;
		}

		//Wav format
		if (isWav)
		{
			if (!OpenWave<IODriver>(fileName, Source->Buffer))
			{
				delete Source;
				LogError("[CALAudioDriver::Load] Can not load file %s", fileName);
				return AL_FALSE;
			}
		}
		else if (isOgg)
		{
			if (!OpenOgg<IODriver>(fileName, Source->Buffer))
			{
				delete Source;
				LogError("[CALAudioDriver::Load] Can not load file %s", fileName);
				return AL_FALSE;
			}
		}
		else
		{
			LogError("[CALAudioDriver::Load] File type is not supported");
			delete Source;
			return AL_FALSE;
		}

		// Bind the buffer with the source.
		alGenSources(1, &(Source->Source));
		if(alGetError() != AL_NO_ERROR)
		{
			return AL_FALSE;
		}

		float tmp[] = {0.0, 0.0, 0.0};
		alSourcei (Source->Source, AL_BUFFER,   Source->Buffer   );
		alSourcef (Source->Source, AL_PITCH,    1.0      );
		alSourcef (Source->Source, AL_GAIN,     1.0      );
		alSourcefv(Source->Source, AL_POSITION, tmp);
		alSourcefv(Source->Source, AL_VELOCITY, tmp);
		alSourcei (Source->Source, AL_LOOPING,  false     );

		m_SoundMapping->AddItem(fileName, Source);

		// Do another error check and return.
		if(alGetError() == AL_NO_ERROR)
		{
			return AL_TRUE;
		}
		else
		{
			return AL_FALSE;
		}
	}


	template <class IODriver> bool CALAudioDriver::OpenWave(const char *nameFile,unsigned int buffer)
	{
		//Check file isValid and file format
		CReaderStream<IODriver> *F = new CReaderStream<IODriver>(nameFile);
		if (F->GetStatus() == ESTREAM_OPEN)
		{
			__UINT8 buff[10];
			F->Read(buff, 0, 4);
			if(memcmp(buff, "RIFF", 4)!= 0)
			{
				SAFE_DEL(F);
				return false;
			}
			
			//unsigned long totalFileLen; 
			//F->Read(&totalFileLen, 4, 1);
			F->Skip(sizeof(__UINT32));

			F->Read(buff, 0, 4);
			if(memcmp(buff, "WAVE", 4)!= 0)
			{
				SAFE_DEL(F);
				return false;
			}

			//Read data and lenData
			__UINT32 lenThis,lenData;

			bool knowd;
			WAVEFORMATEX wfx;
			unsigned char *data;
			while(1)
			{
				F->Read(buff, 0, 4);
				if(F->IsEndOfStream()) 
				{
					break;
				}
				F->ReadUInt32(lenThis);
				knowd=false;
				if(memcmp(buff, "fmt ", 4) == 0)
				{
					knowd=true;
					if(lenThis>sizeof(WAVEFORMATEX))
					{
						F->Read((__UINT8*)&wfx, 0, sizeof(WAVEFORMATEX));
						F->Skip(lenThis-sizeof(WAVEFORMATEX));
					} else
					{
						F->Read((__UINT8*)&wfx, 0, lenThis);
					}
				}
				if (memcmp(buff, "data", 4)== 0)
				{
					knowd=true;
					lenData=lenThis;
					data=new unsigned char [lenData];
					F->Read(data, 0, lenData);
				}
				if(!knowd)
				{
					F->Skip(lenThis);
				}
			};
			SAFE_DEL(F);

			//Set Channel format
			ALenum format;
			if(wfx.nChannels == 1)
			{
				if(wfx.wBitsPerSample == 8)
				{
					format = AL_FORMAT_MONO8;
				}
				else
				{
					format = AL_FORMAT_MONO16;
				}
			} 
			else
			{
				if(wfx.wBitsPerSample == 8)
				{
					format = AL_FORMAT_STEREO8;
				}
				else
				{
					format = AL_FORMAT_STEREO16;
				}
			}
			alBufferData(buffer, format, data, lenData, wfx.nSamplesPerSec);
			SAFE_DEL(data);
			return true;
		}
		SAFE_DEL(F);
		return false;	
	}

	template <class IODriver> bool CALAudioDriver::OpenOgg(const char *nameFile,unsigned int buffer)
	{
		CReaderStream<IODriver> *F = new CReaderStream<IODriver>(nameFile);
		if (F->GetStatus() == ESTREAM_OPEN)
		{
			int buf_size = F->GetLength();
			char * buf = new char[buf_size];
			F->Read((__UINT8*)buf, 0, buf_size);
			SAFE_DEL(F);

			bool re = OpenOgg (buf, buf_size, buffer);
			SAFE_DEL(buf);
			return re;

		}
		return false;
	}
}
#endif