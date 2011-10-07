#ifndef __CSTATEASKSOUND_H__
#define __CSTATEASKSOUND_H__

#include "gametutor.h"
#include "CSoundManagement.h"

using namespace GameTutor;

class CStateAskSound: public CState
{
public:
	CStateAskSound();
	~CStateAskSound() {}

	void Init();
	void Update();
	void Render();
	void Exit();
	void OnControllerEvent(SControllerEvent Event);
private:
	CImage *Background;
	CButton *but_EnableSound;
	CButton *but_DisableSound;
};
#endif