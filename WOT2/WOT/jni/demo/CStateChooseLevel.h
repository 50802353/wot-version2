#ifndef __CSTATECHOOSELEVEL_H__
#define __CSTATECHOOSELEVEL_H__

#include "gametutor.h"
using namespace GameTutor;

class CStateChooseLevel: public CState
{
public:
	CStateChooseLevel();
	~CStateChooseLevel() {}

	void Init();
	void Update();
	void Render();
	void Exit();
	void OnControllerEvent(SControllerEvent Event);
private:
	CImage *background;
	GameSound *A_Background;

	CButton *but_MainMenu;
	CButton *but_Level[9];
};

#endif