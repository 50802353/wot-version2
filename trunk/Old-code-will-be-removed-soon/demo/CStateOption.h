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
	void Exit();
	void OnControllerEvent(SControllerEvent Event);
};
#endif