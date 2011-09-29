#ifndef __CSTATELOGO_H__
#define __CSTATELOGO_H__

#include "gametutor.h"
using namespace GameTutor;

class CStateLogo: public CState
{
public:
	CStateLogo();
	~CStateLogo() {}

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