#ifndef __CSTATEHELP_H__
#define __CSTATEHELP_H__

#include "gametutor.h"
using namespace GameTutor;

class CStateHelp: public CState
{
public:
	CStateHelp();
	~CStateHelp() {}

	void Init();
	void Update();
	void Render();
	void OnControllerEvent(SControllerEvent Event);
	void Exit();
private:
	CImage *Background;
	GameSound* A_Background;

	CButton *but_About;
	CButton *but_Tutorial;
	CButton *but_MainMenu;
};
#endif