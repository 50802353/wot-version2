#include "CAudioPlayer.h"
#include "CAudioDriver.h"
#include "CALAudioDriver.h"
#include "SGameConfig.h"


namespace GameTutor
{
	extern SGameConfig Configuation;
	CAudioPlayer::CAudioPlayer(): m_IsEnable(true)
	{
		m_pAudioDriver = Configuation.pAudioDriver;
		m_IsError = !this->Initialize();

		if (m_IsError) m_IsEnable = false;
	}

	CAudioPlayer::~CAudioPlayer()
	{
		this->Destroy();
		SAFE_DEL(this->m_pAudioDriver);
	}

	bool CAudioPlayer::Initialize ()
	{
		if (m_pAudioDriver->IsAudioDriver(EAUDIO_DRIVER_OPENAL))
		{
			return ((CALAudioDriver*)m_pAudioDriver)->Initialize();
		}
		return false;
	}

	void CAudioPlayer::Destroy()
	{
		if (m_pAudioDriver->IsAudioDriver(EAUDIO_DRIVER_OPENAL))
		{
			((CALAudioDriver*)m_pAudioDriver)->Destroy();
		}
	}

	void CAudioPlayer::Play(const char *name, bool isLoop)
	{
		if (m_IsEnable)
		{	
			if (m_pAudioDriver->IsAudioDriver(EAUDIO_DRIVER_OPENAL))
			{
				((CALAudioDriver*)m_pAudioDriver)->Play(name, isLoop);
			}
		}
	}

	void CAudioPlayer::Pause(const char *name)
	{
		if (m_IsEnable)
		{	
			if (m_pAudioDriver->IsAudioDriver(EAUDIO_DRIVER_OPENAL))
			{
				((CALAudioDriver*)m_pAudioDriver)->Pause(name);
			}
		}
	}

	void CAudioPlayer::Stop(const char *name)
	{
		if (m_IsEnable)
		{	
			if (m_pAudioDriver->IsAudioDriver(EAUDIO_DRIVER_OPENAL))
			{
				((CALAudioDriver*)m_pAudioDriver)->Stop(name);
			}
		}
	}

	bool CAudioPlayer::IsPlaying (const char *name)
	{
		if (m_IsEnable)
		{	
			if (m_pAudioDriver->IsAudioDriver(EAUDIO_DRIVER_OPENAL))
			{
				return ((CALAudioDriver*)m_pAudioDriver)->IsPlaying(name);
			}
		}
		return false;
	}

	void CAudioPlayer::SetVolume(int vol)
	{
		if (m_pAudioDriver->IsAudioDriver(EAUDIO_DRIVER_OPENAL))
		{
			((CALAudioDriver*)m_pAudioDriver)->SetVolume(vol);
		}
	}

	__INT32 CAudioPlayer::GetVolume()
	{
		if (m_pAudioDriver->IsAudioDriver(EAUDIO_DRIVER_OPENAL))
		{
			return ((CALAudioDriver*)m_pAudioDriver)->GetVolume();
		}
		return 0;
	}
}