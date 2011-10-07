#ifndef __CSTATEINGAME_H__
#define __CSTATEINGAME_H__

#include "gametutor.h"
using namespace GameTutor;

class CStateIngame: public CState
{
public:
	CStateIngame();
	~CStateIngame() {}

	void Init();
	void Update();
	void Render();
	void Exit();
};
#endif