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

protected:
	void Init();
	void Destroy();
};

#endif