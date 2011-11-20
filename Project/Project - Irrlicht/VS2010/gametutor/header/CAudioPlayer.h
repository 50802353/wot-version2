#ifndef __C_AUDIO_PLAYER_H__
#define __C_AUDIO_PLAYER_H__

#include "Header.h"
#include "CSingleton.h"
#include "CLookupTableStr.h"
#include "CAudioDriver.h"
#include "CALAudioDriver.h"

namespace GameTutor
{
	class CAudioDriver;

	class CAudioPlayer: public CSingleton<CAudioPlayer>
	{
		friend class CSingleton<CAudioPlayer>;
	protected:
		CAudioPlayer();
	public:
		virtual ~CAudioPlayer();
		void Play(const char *name, bool isLoop);
		void Pause(const char *name);
		void Stop(const char *name);
		bool IsPlaying (const char *name);

		void SetVolume(int vol);
		__INT32 GetVolume();

		void EnableSound(bool val){m_IsEnable = m_IsError?false:val;}
		bool IsEnable() {return m_IsEnable;}
		template <class IODriver> bool Load(const char* fileName,  EAudioMinetype minetype = EAUDIOMINE_AUTO);
	private:
		bool Initialize ();
		void Destroy();
		CAudioDriver *m_pAudioDriver;
		bool m_IsEnable;
		bool m_IsError;
	};
	template <class IODriver> bool CAudioPlayer::Load(const char* fileName, EAudioMinetype minetype)
	{
		if (m_pAudioDriver->IsAudioDriver(EAUDIO_DRIVER_OPENAL))
		{
			return (((CALAudioDriver*)m_pAudioDriver)->Load<IODriver>(fileName, minetype)!=0);
		}
		return false;
	}
}
#endif