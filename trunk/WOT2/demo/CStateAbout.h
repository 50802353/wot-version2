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
	void Exit();
	void OnControllerEvent(SControllerEvent Event);
private:
	__INT32 m_iCount;
};
#endif