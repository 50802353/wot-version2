#ifndef __CSTATEOPTION_H__
#define __CSTATEOPTION_H__

#include "gametutor.h"
using namespace GameTutor;

class CStateOption: public CState
{
public:
	CStateOption();
	~CStateOption() {}

	void Init();
	void Update();
	void Render();
	void OnControllerEvent(SControllerEvent Event);
	void Exit();
	static __UINT32 iVolLevel;
private:
	CImage *Background;
	CImage *Loading;
	GameSound* A_Background;
	CButton* but_Back2MainMenu;
	CButton* but_SoundIsEnable;
	CButton* but_SoundIsMuted;
};
#endif