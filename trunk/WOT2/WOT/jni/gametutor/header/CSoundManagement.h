#ifndef __CSOUNDMANAGEMENT_H__
#define __CSOUNDMANAGEMENT_H__

#include "Header.h"
#include "CSingleton.h"
#include "CResourceLookupTable.h"
#include "SoundDriver.h"
#include "CGame.h"

using namespace std;

namespace GameTutor
{
	class CSoundManagement: public CSingleton<CSoundManagement>, public CResourceLookupTable<GameSound>
	{
		friend class  CSingleton<CSoundManagement>;
	private:
		ALfloat fMasterVolume;
	protected:
		CSoundManagement() {
			fMasterVolume = 0.5f;
		}
	public:
		void AddSound(char* SoundFileName, const char* nameKey)
		{
			GameSound *_result = GetSound (nameKey);
			if (!_result)
			{
				if (CGame::GetInstance()->HasSound())
				{
					_result = new GameSound(SoundFileName);
					_result->VolumeControl(fMasterVolume);
					this->Add(nameKey,_result);
				}
			}
			else _result->VolumeControl(fMasterVolume);
		}
		GameSound* GetSound(const char* soundName)
		{
			if (CGame::GetInstance()->HasSound())
			{
				GameSound* _result = this->Get(soundName);
				if (_result) {
					_result->VolumeControl(fMasterVolume);
					return _result;
				} else return NULL;
			}
			else {
				Log("Sound: Sound is Disable");
				return NULL;
			}
		}
		void PlaySound(const char* soundName)
		{
			GameSound* sound = this->GetSound(soundName);
			if(sound) {
				sound->Play(fMasterVolume);
			}
		}

		void SetSound (bool SoundStatus){			
			if (!SoundStatus) {
				CloseSoundDevice();
				CGame::GetInstance()->SetSound(SoundStatus);
				this->Clean();
			}
			else CGame::GetInstance()->SetSound(SoundStatus);
		}

		void SetMasterVolume(float _volume){
			fMasterVolume = _volume;
		}

		float GetMasterVolume(){
			return fMasterVolume;
		}

		virtual ~CSoundManagement() {}
	};
}

#endif