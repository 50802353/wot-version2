#ifndef __CEXAMPLE_H__
#define __CEXAMPLE_H__
#include "gametutor.h"

using namespace GameTutor;

class CExample:public CGame
{
public:
	CExample(): CGame() {}
	virtual ~CExample() {}
	virtual bool OnControllerEvent(SControllerEvent Event)
	{
		if (Event.Type == ECE_KEY && Event.KeyData.Event == EKE_PRESSED && Event.KeyData.KeyCode == EKEY_WIN_Q)
		{
			this->Exit();
			return true;
		}
		return false;
	}
	static float m_fMasterVolume;
	static __UINT16 m_LevelUnlocked;
	static __UINT16 m_LevelChose;
protected:
	void Init();
	void Destroy();
};

#endif