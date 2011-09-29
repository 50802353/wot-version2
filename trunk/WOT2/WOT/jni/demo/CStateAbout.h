#ifndef __CSTATEABOUT_H__
#define __CSTATEABOUT_H__

#include "gametutor.h"
using namespace GameTutor;

class CStateAbout: public CState
{
public:
	CStateAbout();
	~CStateAbout() {}

	void Init();
	void Update();
	void Render();
	void OnControllerEvent(SControllerEvent Event);
	void Exit();
private:
	CImage *Logo;
	GameSound* A_Background;
};
#endif