#ifndef __C_AUDIO_DRIVER_H__
#define __C_AUDIO_DRIVER_H__

#include "Header.h"
#include "CSingleton.h"
namespace GameTutor
{
	enum EAudioDriver
	{
		EAUDIO_DRIVER_OPENAL,
	};

	enum EAudioMinetype
	{
		EAUDIOMINE_AUTO,
		EAUDIOMINE_WAV,
		EAUDIOMINE_OGG,
	};

	typedef struct tWAVEFORMATEX
	{
		unsigned short		wFormatTag;         /* format type */
		unsigned short		nChannels;          /* number of channels (i.e. mono, stereo...) */
		unsigned long		nSamplesPerSec;     /* sample rate */
		unsigned long       nAvgBytesPerSec;    /* for buffer estimation */
		unsigned short		nBlockAlign;        /* block size of data */
		unsigned short		wBitsPerSample;     /* number of bits per sample of mono data */
		unsigned short		cbSize;             /* the count in bytes of the size of */
		/* extra information (after cbSize) */
	} WAVEFORMATEX;

	class CAudioDriver
	{
	public:
		CAudioDriver(EAudioDriver driver);
		bool IsAudioDriver(EAudioDriver driver);
		virtual ~CAudioDriver(){}
	protected:
		EAudioDriver m_AudioDriver;
	};
}

#endif